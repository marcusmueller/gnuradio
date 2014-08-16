"""
Copyright 2007-2011 Free Software Foundation, Inc.
This file is part of GNU Radio

GNU Radio Companion is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

GNU Radio Companion is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
"""

import os
import signal
from Constants import IMAGE_FILE_EXTENSION
import Actions
import pygtk
pygtk.require('2.0')
import gtk
import gobject
import subprocess
import Preferences
from threading import Thread
import Messages
from .. base import ParseXML
from MainWindow import MainWindow
from PropsDialog import PropsDialog
from ParserErrorsDialog import ParserErrorsDialog
import Dialogs
from FileDialogs import OpenFlowGraphFileDialog, SaveFlowGraphFileDialog, SaveImageFileDialog

gobject.threads_init()

class ActionHandler:
    """
    The action handler will setup all the major window components,
    and handle button presses and flow graph operations from the GUI.
    """

    def __init__(self, file_paths, platform):
        """
        ActionHandler constructor.
        Create the main window, setup the message handler, import the preferences,
        and connect all of the action handlers. Finally, enter the gtk main loop and block.

        Args:
            file_paths: a list of flow graph file passed from command line
            platform: platform module
        """
        self.clipboard = None
        for action in Actions.get_all_actions(): action.connect('activate', self._handle_action)
        #setup the main window
        self.platform = platform;
        self.main_window = MainWindow(platform)
        self.main_window.connect('delete-event', self._quit)
        self.main_window.connect('key-press-event', self._handle_key_press)
        self.get_page = self.main_window.get_page
        self.get_flow_graph = self.main_window.get_flow_graph
        self.get_focus_flag = self.main_window.get_focus_flag
        #setup the messages
        Messages.register_messenger(self.main_window.add_report_line)
        Messages.send_init(platform)
        #initialize
        self.init_file_paths = file_paths
        Actions.APPLICATION_INITIALIZE()
        #enter the mainloop
        gtk.main()

    def _handle_key_press(self, widget, event):
        """
        Handle key presses from the keyboard and translate key combinations into actions.
        This key press handler is called prior to the gtk key press handler.
        This handler bypasses built in accelerator key handling when in focus because
        * some keys are ignored by the accelerators like the direction keys,
        * some keys are not registered to any accelerators but are still used.
        When not in focus, gtk and the accelerators handle the the key press.

        Returns:
            false to let gtk handle the key action
        """
        # prevent key event stealing while the search box is active
        if self.main_window.btwin.search_entry.has_focus(): return False
        if not self.get_focus_flag(): return False
        return Actions.handle_key_press(event)

    def _quit(self, window, event):
        """
        Handle the delete event from the main window.
        Generated by pressing X to close, alt+f4, or right click+close.
        This method in turns calls the state handler to quit.

        Returns:
            true
        """
        Actions.APPLICATION_QUIT()
        return True

    def _handle_action(self, action):
        #print action
        ##################################################
        # Initalize/Quit
        ##################################################
        if action == Actions.APPLICATION_INITIALIZE:
            for action in Actions.get_all_actions(): action.set_sensitive(False) #set all actions disabled
            #enable a select few actions
            for action in (
                Actions.APPLICATION_QUIT, Actions.FLOW_GRAPH_NEW,
                Actions.FLOW_GRAPH_OPEN, Actions.FLOW_GRAPH_SAVE_AS,
                Actions.FLOW_GRAPH_CLOSE, Actions.ABOUT_WINDOW_DISPLAY,
                Actions.FLOW_GRAPH_SCREEN_CAPTURE, Actions.HELP_WINDOW_DISPLAY,
                Actions.TYPES_WINDOW_DISPLAY, Actions.TOGGLE_BLOCKS_WINDOW,
                Actions.TOGGLE_REPORTS_WINDOW, Actions.TOGGLE_HIDE_DISABLED_BLOCKS,
                Actions.TOOLS_RUN_FDESIGN, Actions.TOGGLE_SCROLL_LOCK, Actions.CLEAR_REPORTS,
                Actions.TOGGLE_AUTO_HIDE_PORT_LABELS,
                Actions.TOOLS_RUN_TASK_UI
            ): action.set_sensitive(True)
            if ParseXML.xml_failures:
                Messages.send_xml_errors_if_any(ParseXML.xml_failures)
                Actions.XML_PARSER_ERRORS_DISPLAY.set_sensitive(True)

            if not self.init_file_paths:
                self.init_file_paths = Preferences.files_open()
            if not self.init_file_paths: self.init_file_paths = ['']
            for file_path in self.init_file_paths:
                if file_path: self.main_window.new_page(file_path) #load pages from file paths
            if Preferences.file_open() in self.init_file_paths:
                self.main_window.new_page(Preferences.file_open(), show=True)
            if not self.get_page(): self.main_window.new_page() #ensure that at least a blank page exists

            self.main_window.btwin.search_entry.hide()
            Actions.TOGGLE_REPORTS_WINDOW.set_active(Preferences.reports_window_visibility())
            Actions.TOGGLE_BLOCKS_WINDOW.set_active(Preferences.blocks_window_visibility())
            Actions.TOGGLE_SCROLL_LOCK.set_active(Preferences.scroll_lock())
            Actions.TOGGLE_AUTO_HIDE_PORT_LABELS.set_active(Preferences.auto_hide_port_labels())
        elif action == Actions.APPLICATION_QUIT:
            if self.main_window.close_pages():
                gtk.main_quit()
                exit(0)
        ##################################################
        # Selections
        ##################################################
        elif action == Actions.ELEMENT_SELECT:
            pass #do nothing, update routines below
        elif action == Actions.NOTHING_SELECT:
            self.get_flow_graph().unselect()
        ##################################################
        # Enable/Disable
        ##################################################
        elif action == Actions.BLOCK_ENABLE:
            if self.get_flow_graph().enable_selected(True):
                self.get_flow_graph().update()
                self.get_page().get_state_cache().save_new_state(self.get_flow_graph().export_data())
                self.get_page().set_saved(False)
        elif action == Actions.BLOCK_DISABLE:
            if self.get_flow_graph().enable_selected(False):
                self.get_flow_graph().update()
                self.get_page().get_state_cache().save_new_state(self.get_flow_graph().export_data())
                self.get_page().set_saved(False)
        ##################################################
        # Cut/Copy/Paste
        ##################################################
        elif action == Actions.BLOCK_CUT:
            Actions.BLOCK_COPY()
            Actions.ELEMENT_DELETE()
        elif action == Actions.BLOCK_COPY:
            self.clipboard = self.get_flow_graph().copy_to_clipboard()
        elif action == Actions.BLOCK_PASTE:
            if self.clipboard:
                self.get_flow_graph().paste_from_clipboard(self.clipboard)
                self.get_flow_graph().update()
                self.get_page().get_state_cache().save_new_state(self.get_flow_graph().export_data())
                self.get_page().set_saved(False)
                ##################################################
                # Create heir block
                ##################################################
        elif action == Actions.BLOCK_CREATE_HIER:

                        # keeping track of coordinates for pasting later
                        coords = self.get_flow_graph().get_selected_blocks()[0].get_coordinate()
                        x,y = coords
                        x_min = x
                        y_min = y

                        pads = [];
                        params = [];

                        # Save the state of the leaf blocks
                        for block in self.get_flow_graph().get_selected_blocks():

                            # Check for string variables within the blocks
                            for param in block.get_params():
                                for variable in self.get_flow_graph().get_variables():
                                    # If a block parameter exists that is a variable, create a parameter for it
                                    if param.get_value() == variable.get_id():
                                        params.append(param.get_value())
                                for flow_param in self.get_flow_graph().get_parameters():
                                    # If a block parameter exists that is a parameter, create a parameter for it
                                    if param.get_value() == flow_param.get_id():
                                        params.append(param.get_value())


                            # keep track of x,y mins for pasting later
                            (x,y) = block.get_coordinate()
                            if x < x_min:
                                x_min = x
                            if y < y_min:
                                y_min = y

                            for connection in block.get_connections():

                                # Get id of connected blocks
                                source_id = connection.get_source().get_parent().get_id()
                                sink_id = connection.get_sink().get_parent().get_id()

                                # If connected block is not in the list of selected blocks create a pad for it
                                if self.get_flow_graph().get_block(source_id) not in self.get_flow_graph().get_selected_blocks():
                                    pads.append({'key': connection.get_sink().get_key(), 'coord': connection.get_source().get_coordinate(), 'block_id' : block.get_id(), 'direction': 'source'})

                                if self.get_flow_graph().get_block(sink_id) not in self.get_flow_graph().get_selected_blocks():
                                    pads.append({'key': connection.get_source().get_key(), 'coord': connection.get_sink().get_coordinate(), 'block_id' : block.get_id(), 'direction': 'sink'})


                        # Copy the selected blocks and paste them into a new page
                        #   then move the flowgraph to a reasonable position
                        Actions.BLOCK_COPY()
                        self.main_window.new_page()
                        Actions.BLOCK_PASTE()
                        coords = (x_min,y_min)
                        self.get_flow_graph().move_selected(coords)


                        # Set flow graph to heir block type
                        top_block  = self.get_flow_graph().get_block("top_block")
                        top_block.get_param('generate_options').set_value('hb')

                        # this needs to be a unique name
                        top_block.get_param('id').set_value('new_heir')

                        # Remove the default samp_rate variable block that is created
                        remove_me  = self.get_flow_graph().get_block("samp_rate")
                        self.get_flow_graph().remove_element(remove_me)


                        # Add the param blocks along the top of the window
                        x_pos = 150
                        for param in params:
                            param_id = self.get_flow_graph().add_new_block('parameter',(x_pos,10))
                            param_block = self.get_flow_graph().get_block(param_id)
                            param_block.get_param('id').set_value(param)
                            x_pos = x_pos + 100

                        for pad in pads:
                            # Add the pad sources and sinks within the new heir block
                            if pad['direction'] == 'sink':

                                # Add new PAD_SINK block to the canvas
                                pad_id = self.get_flow_graph().add_new_block('pad_sink', pad['coord'])

                                # setup the references to the sink and source
                                pad_block = self.get_flow_graph().get_block(pad_id)
                                pad_sink = pad_block.get_sinks()[0]

                                source_block = self.get_flow_graph().get_block(pad['block_id'])
                                source = source_block.get_source(pad['key'])

                                # Ensure the port types match
                                while pad_sink.get_type() != source.get_type():

                                    # Special case for some blocks that have non-standard type names, e.g. uhd
                                    if pad_sink.get_type() == 'complex' and source.get_type() == 'fc32':
                                        break;
                                    pad_block.type_controller_modify(1)

                                # Connect the pad to the proper sinks
                                new_connection = self.get_flow_graph().connect(source,pad_sink)

                            elif pad['direction'] == 'source':
                                pad_id = self.get_flow_graph().add_new_block('pad_source', pad['coord'])

                                # setup the references to the sink and source
                                pad_block = self.get_flow_graph().get_block(pad_id)
                                pad_source = pad_block.get_sources()[0]

                                sink_block = self.get_flow_graph().get_block(pad['block_id'])
                                sink = sink_block.get_sink(pad['key'])

                                # Ensure the port types match
                                while sink.get_type() != pad_source.get_type():
                                    # Special case for some blocks that have non-standard type names, e.g. uhd
                                    if pad_source.get_type() == 'complex' and sink.get_type() == 'fc32':
                                        break;
                                    pad_block.type_controller_modify(1)

                                # Connect the pad to the proper sinks
                                new_connection = self.get_flow_graph().connect(pad_source,sink)

                        # update the new heir block flow graph
                        self.get_flow_graph().update()


        ##################################################
        # Move/Rotate/Delete/Create
        ##################################################
        elif action == Actions.BLOCK_MOVE:
            self.get_page().get_state_cache().save_new_state(self.get_flow_graph().export_data())
            self.get_page().set_saved(False)
        elif action == Actions.BLOCK_ROTATE_CCW:
            if self.get_flow_graph().rotate_selected(90):
                self.get_flow_graph().update()
                self.get_page().get_state_cache().save_new_state(self.get_flow_graph().export_data())
                self.get_page().set_saved(False)
        elif action == Actions.BLOCK_ROTATE_CW:
            if self.get_flow_graph().rotate_selected(-90):
                self.get_flow_graph().update()
                self.get_page().get_state_cache().save_new_state(self.get_flow_graph().export_data())
                self.get_page().set_saved(False)
        elif action == Actions.ELEMENT_DELETE:
            if self.get_flow_graph().remove_selected():
                self.get_flow_graph().update()
                self.get_page().get_state_cache().save_new_state(self.get_flow_graph().export_data())
                Actions.NOTHING_SELECT()
                self.get_page().set_saved(False)
        elif action == Actions.ELEMENT_CREATE:
            self.get_flow_graph().update()
            self.get_page().get_state_cache().save_new_state(self.get_flow_graph().export_data())
            Actions.NOTHING_SELECT()
            self.get_page().set_saved(False)
        elif action == Actions.BLOCK_INC_TYPE:
            if self.get_flow_graph().type_controller_modify_selected(1):
                self.get_flow_graph().update()
                self.get_page().get_state_cache().save_new_state(self.get_flow_graph().export_data())
                self.get_page().set_saved(False)
        elif action == Actions.BLOCK_DEC_TYPE:
            if self.get_flow_graph().type_controller_modify_selected(-1):
                self.get_flow_graph().update()
                self.get_page().get_state_cache().save_new_state(self.get_flow_graph().export_data())
                self.get_page().set_saved(False)
        elif action == Actions.PORT_CONTROLLER_INC:
            if self.get_flow_graph().port_controller_modify_selected(1):
                self.get_flow_graph().update()
                self.get_page().get_state_cache().save_new_state(self.get_flow_graph().export_data())
                self.get_page().set_saved(False)
        elif action == Actions.PORT_CONTROLLER_DEC:
            if self.get_flow_graph().port_controller_modify_selected(-1):
                self.get_flow_graph().update()
                self.get_page().get_state_cache().save_new_state(self.get_flow_graph().export_data())
                self.get_page().set_saved(False)
        ##################################################
        # Window stuff
        ##################################################
        elif action == Actions.ABOUT_WINDOW_DISPLAY:
            Dialogs.AboutDialog(self.get_flow_graph().get_parent())
        elif action == Actions.HELP_WINDOW_DISPLAY:
            Dialogs.HelpDialog()
        elif action == Actions.TYPES_WINDOW_DISPLAY:
            Dialogs.TypesDialog(self.get_flow_graph().get_parent())
        elif action == Actions.ERRORS_WINDOW_DISPLAY:
            Dialogs.ErrorsDialog(self.get_flow_graph())
        elif action == Actions.TOGGLE_REPORTS_WINDOW:
            visible = action.get_active()
            if visible:
                self.main_window.reports_scrolled_window.show()
            else:
                self.main_window.reports_scrolled_window.hide()
            Preferences.reports_window_visibility(visible)
        elif action == Actions.TOGGLE_BLOCKS_WINDOW:
            visible = action.get_active()
            if visible:
                self.main_window.btwin.show()
            else:
                self.main_window.btwin.hide()
            Preferences.blocks_window_visibility(visible)
        elif action == Actions.TOGGLE_SCROLL_LOCK:
            visible = action.get_active()
            self.main_window.text_display.scroll_lock = visible
            if visible:
                self.main_window.text_display.scroll_to_end()
        elif action == Actions.CLEAR_REPORTS:
            self.main_window.text_display.clear()
        elif action == Actions.TOGGLE_HIDE_DISABLED_BLOCKS:
            Actions.NOTHING_SELECT()
        elif action == Actions.TOGGLE_AUTO_HIDE_PORT_LABELS:
            Preferences.auto_hide_port_labels(action.get_active())
            self.main_window.get_flow_graph().create_shapes()
        ##################################################
        # Param Modifications
        ##################################################
        elif action == Actions.BLOCK_PARAM_MODIFY:
            selected_block = self.get_flow_graph().get_selected_block()
            if selected_block:
                if PropsDialog(selected_block).run():
                    #save the new state
                    self.get_flow_graph().update()
                    self.get_page().get_state_cache().save_new_state(self.get_flow_graph().export_data())
                    self.get_page().set_saved(False)
                else:
                    #restore the current state
                    n = self.get_page().get_state_cache().get_current_state()
                    self.get_flow_graph().import_data(n)
                    self.get_flow_graph().update()
        ##################################################
        # View Parser Errors
        ##################################################
        elif action == Actions.XML_PARSER_ERRORS_DISPLAY:
            ParserErrorsDialog(ParseXML.xml_failures).run()
        ##################################################
        # Undo/Redo
        ##################################################
        elif action == Actions.FLOW_GRAPH_UNDO:
            n = self.get_page().get_state_cache().get_prev_state()
            if n:
                self.get_flow_graph().unselect()
                self.get_flow_graph().import_data(n)
                self.get_flow_graph().update()
                self.get_page().set_saved(False)
        elif action == Actions.FLOW_GRAPH_REDO:
            n = self.get_page().get_state_cache().get_next_state()
            if n:
                self.get_flow_graph().unselect()
                self.get_flow_graph().import_data(n)
                self.get_flow_graph().update()
                self.get_page().set_saved(False)
        ##################################################
        # New/Open/Save/Close
        ##################################################
        elif action == Actions.FLOW_GRAPH_NEW:
            self.main_window.new_page()
        elif action == Actions.FLOW_GRAPH_OPEN:
            file_paths = OpenFlowGraphFileDialog(self.get_page().get_file_path()).run()
            if file_paths: #open a new page for each file, show only the first
                for i,file_path in enumerate(file_paths):
                    self.main_window.new_page(file_path, show=(i==0))
        elif action == Actions.FLOW_GRAPH_CLOSE:
            self.main_window.close_page()
        elif action == Actions.FLOW_GRAPH_SAVE:
            #read-only or undefined file path, do save-as
            if self.get_page().get_read_only() or not self.get_page().get_file_path():
                Actions.FLOW_GRAPH_SAVE_AS()
            #otherwise try to save
            else:
                try:
                    ParseXML.to_file(self.get_flow_graph().export_data(), self.get_page().get_file_path())
                    self.get_flow_graph().grc_file_path = self.get_page().get_file_path()
                    self.get_page().set_saved(True)
                except IOError:
                    Messages.send_fail_save(self.get_page().get_file_path())
                    self.get_page().set_saved(False)
        elif action == Actions.FLOW_GRAPH_SAVE_AS:
            file_path = SaveFlowGraphFileDialog(self.get_page().get_file_path()).run()
            if file_path is not None:
                self.get_page().set_file_path(file_path)
                Actions.FLOW_GRAPH_SAVE()
        elif action == Actions.FLOW_GRAPH_SCREEN_CAPTURE:
            file_path = SaveImageFileDialog(self.get_page().get_file_path()).run()
            if file_path is not None:
                pixbuf = self.get_flow_graph().get_drawing_area().get_pixbuf()
                pixbuf.save(file_path, IMAGE_FILE_EXTENSION[1:])
        ##################################################
        # Gen/Exec/Stop
        ##################################################
        elif action == Actions.FLOW_GRAPH_GEN:
            if not self.get_page().get_proc():
                if not self.get_page().get_saved() or not self.get_page().get_file_path():
                    Actions.FLOW_GRAPH_SAVE() #only save if file path missing or not saved
                if self.get_page().get_saved() and self.get_page().get_file_path():
                    generator = self.get_page().get_generator()
                    try:
                        Messages.send_start_gen(generator.get_file_path())
                        generator.write()
                    except Exception,e: Messages.send_fail_gen(e)
                else: self.generator = None
        elif action == Actions.FLOW_GRAPH_EXEC:
            if not self.get_page().get_proc():
                Actions.FLOW_GRAPH_GEN()
                if self.get_page().get_saved() and self.get_page().get_file_path():
                    ExecFlowGraphThread(self)
        elif action == Actions.FLOW_GRAPH_KILL:
            if self.get_page().get_proc():
                try: self.get_page().get_proc().kill()
                except: print "could not kill process: %d"%self.get_page().get_proc().pid
        elif action == Actions.PAGE_CHANGE: #pass and run the global actions
            pass
        elif action == Actions.RELOAD_BLOCKS:
            self.platform.load_blocks()
            self.main_window.btwin.clear()
            self.platform.load_block_tree(self.main_window.btwin)
            Actions.XML_PARSER_ERRORS_DISPLAY.set_sensitive(bool(ParseXML.xml_failures))
            Messages.send_xml_errors_if_any(ParseXML.xml_failures)
        elif action == Actions.FIND_BLOCKS:
            self.main_window.btwin.show()
            self.main_window.btwin.search_entry.show()
            self.main_window.btwin.search_entry.grab_focus()
        elif action == Actions.OPEN_HIER:
            bn = [];
            for b in self.get_flow_graph().get_selected_blocks():
                if b._grc_source:
                    self.main_window.new_page(b._grc_source, show=True)
        elif action == Actions.BUSSIFY_SOURCES:
            n = {'name':'bus', 'type':'bus'}
            for b in self.get_flow_graph().get_selected_blocks():
                b.bussify(n, 'source')
            self.get_flow_graph()._old_selected_port = None
            self.get_flow_graph()._new_selected_port = None
            Actions.ELEMENT_CREATE()

        elif action == Actions.BUSSIFY_SINKS:
            n = {'name':'bus', 'type':'bus'}
            for b in self.get_flow_graph().get_selected_blocks():
                b.bussify(n, 'sink')
            self.get_flow_graph()._old_selected_port = None
            self.get_flow_graph()._new_selected_port = None
            Actions.ELEMENT_CREATE()

        elif action == Actions.TOOLS_RUN_FDESIGN:
            subprocess.Popen('gr_filter_design',
                             shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        elif action == Actions.TOOLS_RUN_TASK_UI:
            print "starting task frontend"
            if not self.get_page().get_saved() or not self.get_page().get_file_path():
                Actions.FLOW_GRAPH_SAVE() #only save if file path missing or not saved
            subprocess.Popen('task_frontend -g '+ self.get_page().get_file_path(), 
                             shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

        else:
            print '!!! Action "%s" not handled !!!' % action
        ##################################################
        # Global Actions for all States
        ##################################################
        #update general buttons
        Actions.ERRORS_WINDOW_DISPLAY.set_sensitive(not self.get_flow_graph().is_valid())
        Actions.ELEMENT_DELETE.set_sensitive(bool(self.get_flow_graph().get_selected_elements()))
        Actions.BLOCK_PARAM_MODIFY.set_sensitive(bool(self.get_flow_graph().get_selected_block()))
        Actions.BLOCK_ROTATE_CCW.set_sensitive(bool(self.get_flow_graph().get_selected_blocks()))
        Actions.BLOCK_ROTATE_CW.set_sensitive(bool(self.get_flow_graph().get_selected_blocks()))
        #update cut/copy/paste
        Actions.BLOCK_CUT.set_sensitive(bool(self.get_flow_graph().get_selected_blocks()))
        Actions.BLOCK_COPY.set_sensitive(bool(self.get_flow_graph().get_selected_blocks()))
        Actions.BLOCK_PASTE.set_sensitive(bool(self.clipboard))
        #update enable/disable
        Actions.BLOCK_ENABLE.set_sensitive(bool(self.get_flow_graph().get_selected_blocks()))
        Actions.BLOCK_DISABLE.set_sensitive(bool(self.get_flow_graph().get_selected_blocks()))
        Actions.BLOCK_CREATE_HIER.set_sensitive(bool(self.get_flow_graph().get_selected_blocks()))
        Actions.OPEN_HIER.set_sensitive(bool(self.get_flow_graph().get_selected_blocks()))
        Actions.BUSSIFY_SOURCES.set_sensitive(bool(self.get_flow_graph().get_selected_blocks()))
        Actions.BUSSIFY_SINKS.set_sensitive(bool(self.get_flow_graph().get_selected_blocks()))
        Actions.RELOAD_BLOCKS.set_sensitive(True)
        Actions.FIND_BLOCKS.set_sensitive(True)
        #set the exec and stop buttons
        self.update_exec_stop()
        #saved status
        Actions.FLOW_GRAPH_SAVE.set_sensitive(not self.get_page().get_saved())
        self.main_window.update()
        try: #set the size of the flow graph area (if changed)
            new_size = self.get_flow_graph().get_option('window_size')
            if self.get_flow_graph().get_size() != tuple(new_size):
                self.get_flow_graph().set_size(*new_size)
        except: pass
        #draw the flow graph
        self.get_flow_graph().update_selected()
        self.get_flow_graph().queue_draw()
        return True #action was handled

    def update_exec_stop(self):
        """
        Update the exec and stop buttons.
        Lock and unlock the mutex for race conditions with exec flow graph threads.
        """
        sensitive = self.get_flow_graph().is_valid() and not self.get_page().get_proc()
        Actions.FLOW_GRAPH_GEN.set_sensitive(sensitive)
        Actions.FLOW_GRAPH_EXEC.set_sensitive(sensitive)
        Actions.FLOW_GRAPH_KILL.set_sensitive(self.get_page().get_proc() != None)

class ExecFlowGraphThread(Thread):
    """Execute the flow graph as a new process and wait on it to finish."""

    def __init__ (self, action_handler):
        """
        ExecFlowGraphThread constructor.

        Args:
            action_handler: an instance of an ActionHandler
        """
        Thread.__init__(self)
        self.update_exec_stop = action_handler.update_exec_stop
        self.flow_graph = action_handler.get_flow_graph()
        #store page and dont use main window calls in run
        self.page = action_handler.get_page()
        Messages.send_start_exec(self.page.get_generator().get_file_path())
        #get the popen
        try:
            self.p = self.page.get_generator().get_popen()
            self.page.set_proc(self.p)
            #update
            self.update_exec_stop()
            self.start()
        except Exception, e:
            Messages.send_verbose_exec(str(e))
            Messages.send_end_exec()

    def run(self):
        """
        Wait on the executing process by reading from its stdout.
        Use gobject.idle_add when calling functions that modify gtk objects.
        """
        #handle completion
        r = "\n"
        while(r):
            gobject.idle_add(Messages.send_verbose_exec, r)
            r = os.read(self.p.stdout.fileno(), 1024)
        gobject.idle_add(self.done)

    def done(self):
        """Perform end of execution tasks."""
        Messages.send_end_exec()
        self.page.set_proc(None)
        self.update_exec_stop()
