/* -*- c++ -*- */
/*
 * Copyright 2015 Free Software Foundation, Inc.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef INCLUDED_DTV_DVBT2_FRAMEMAPPER_CC_IMPL_H
#define INCLUDED_DTV_DVBT2_FRAMEMAPPER_CC_IMPL_H

#include "../dvb/dvb_defines.h"

#include <gnuradio/dtv/dvbt2_framemapper_cc.h>

#define KBCH_1_4 3072
#define NBCH_1_4 3240
#define KBCH_1_2 7032
#define NBCH_1_2 7200

#define KSIG_PRE 200
#define KSIG_POST 350
#define NBCH_PARITY 168

struct L1Pre {
    int type;
    int bwt_ext;
    int s1;
    int s2;
    int l1_repetition_flag;
    int guard_interval;
    int papr;
    int l1_mod;
    int l1_cod;
    int l1_fec_type;
    int l1_post_size;
    int l1_post_info_size;
    int pilot_pattern;
    int tx_id_availability;
    int cell_id;
    int network_id;
    int t2_system_id;
    int num_t2_frames;
    int num_data_symbols;
    int regen_flag;
    int l1_post_extension;
    int num_rf;
    int current_rf_index;
    int t2_version;
    int l1_post_scrambled;
    int t2_base_lite;
    int reserved;
    int crc_32;
};

struct L1Post {
    int sub_slices_per_frame;
    int num_plp;
    int num_aux;
    int aux_config_rfu;
    int rf_idx;
    int frequency;
    int plp_id;
    int plp_type;
    int plp_payload_type;
    int ff_flag;
    int first_rf_idx;
    int first_frame_idx;
    int plp_group_id;
    int plp_cod;
    int plp_mod;
    int plp_rotation;
    int plp_fec_type;
    int plp_num_blocks_max;
    int frame_interval;
    int time_il_length;
    int time_il_type;
    int in_band_a_flag;
    int in_band_b_flag;
    int reserved_1;
    int plp_mode;
    int static_flag;
    int static_padding_flag;
    int fef_length_msb;
    int reserved_2;
    int frame_idx;
    int sub_slice_interval;
    int type_2_start;
    int l1_change_counter;
    int start_rf_idx;
    int reserved_3;
    int plp_id_dynamic;
    int plp_start;
    int plp_num_blocks;
    int reserved_4;
    int reserved_5;
};

struct L1Signalling {
    L1Pre l1pre_data;
    L1Post l1post_data;
};

struct l1pre_ldpc_encode_table {
    int table_length;
    int d[LDPC_ENCODE_TABLE_LENGTH];
    int p[LDPC_ENCODE_TABLE_LENGTH];
};

struct l1post_ldpc_encode_table {
    int table_length;
    int d[LDPC_ENCODE_TABLE_LENGTH];
    int p[LDPC_ENCODE_TABLE_LENGTH];
};

namespace gr {
namespace dtv {

class dvbt2_framemapper_cc_impl : public dvbt2_framemapper_cc
{
private:
    int cell_size;
    int stream_items;
    int mapped_items;
    int l1_constellation;
    int fft_size;
    int eta_mod;
    int t2_frames;
    int t2_frame_num;
    int l1_scrambled;
    int N_P2;
    int C_P2;
    int N_FC;
    int C_FC;
    int C_DATA;
    int N_post;
    int N_punc;
    L1Signalling L1_Signalling[1];
    void add_l1pre(gr_complex*);
    void add_l1post(gr_complex*, int);
    int add_crc32_bits(unsigned char*, int);
    unsigned int m_poly_s_12[6];
    int poly_mult(const int*, int, const int*, int, int*);
    void poly_pack(const int*, unsigned int*, int);
    void poly_reverse(int*, int*, int);
    inline void reg_6_shift(unsigned int*);
    void bch_poly_build_tables(void);
    void l1pre_ldpc_lookup_generate(void);
    void l1post_ldpc_lookup_generate(void);
    void init_dummy_randomizer(void);
    void init_l1_randomizer(void);
    l1pre_ldpc_encode_table l1pre_ldpc_encode;
    l1post_ldpc_encode_table l1post_ldpc_encode;
    unsigned char l1_temp[FRAME_SIZE_SHORT];
    unsigned char l1_interleave[FRAME_SIZE_SHORT];
    unsigned char l1_map[KBCH_1_2];
    unsigned char l1_randomize[KBCH_1_2];
    gr_complex* zigzag_interleave;
    gr_complex* dummy_randomize;
    gr_complex l1pre_cache[1840];
    gr_complex unmodulated;
    gr_complex m_bpsk[2];
    gr_complex m_qpsk[4];
    gr_complex m_16qam[16];
    gr_complex m_64qam[64];

    const static int ldpc_tab_1_4S[9][13];
    const static int ldpc_tab_1_2S[20][9];

    const static int pre_puncture[36];
    const static int post_padding_bqpsk[20];
    const static int post_padding_16qam[20];
    const static int post_padding_64qam[20];
    const static int post_puncture_bqpsk[25];
    const static int post_puncture_16qam[25];
    const static int post_puncture_64qam[25];

    const static int mux16[8];
    const static int mux64[12];

public:
    dvbt2_framemapper_cc_impl(dvb_framesize_t framesize,
                              dvb_code_rate_t rate,
                              dvb_constellation_t constellation,
                              dvbt2_rotation_t rotation,
                              int fecblocks,
                              int tiblocks,
                              dvbt2_extended_carrier_t carriermode,
                              dvbt2_fftsize_t fftsize,
                              dvb_guardinterval_t guardinterval,
                              dvbt2_l1constellation_t l1constellation,
                              dvbt2_pilotpattern_t pilotpattern,
                              int t2frames,
                              int numdatasyms,
                              dvbt2_papr_t paprmode,
                              dvbt2_version_t version,
                              dvbt2_preamble_t preamble,
                              dvbt2_inputmode_t inputmode,
                              dvbt2_reservedbiasbits_t reservedbiasbits,
                              dvbt2_l1scrambled_t l1scrambled,
                              dvbt2_inband_t inband);
    ~dvbt2_framemapper_cc_impl() override;

    void forecast(int noutput_items, gr_vector_int& ninput_items_required) override;

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items) override;
};

} // namespace dtv
} // namespace gr

#endif /* INCLUDED_DTV_DVBT2_FRAMEMAPPER_CC_IMPL_H */
