/*!The Treasure Box Library
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * Copyright (C) 2009 - 2019, TBOOX Open Source Group.
 *
 * @author      ruki
 * @file        crc16.c
 * @ingroup     hash
 *
 */

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "crc16.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * globals
 */

// the crc16(ANSI) table
tb_uint16_t const g_crc16_table[] = 
{
    0x0000, 0x0580, 0x0f80, 0x0a00, 0x1b80, 0x1e00, 0x1400, 0x1180
,	0x3380, 0x3600, 0x3c00, 0x3980, 0x2800, 0x2d80, 0x2780, 0x2200
,	0x6380, 0x6600, 0x6c00, 0x6980, 0x7800, 0x7d80, 0x7780, 0x7200
,	0x5000, 0x5580, 0x5f80, 0x5a00, 0x4b80, 0x4e00, 0x4400, 0x4180
,	0xc380, 0xc600, 0xcc00, 0xc980, 0xd800, 0xdd80, 0xd780, 0xd200
,	0xf000, 0xf580, 0xff80, 0xfa00, 0xeb80, 0xee00, 0xe400, 0xe180
,	0xa000, 0xa580, 0xaf80, 0xaa00, 0xbb80, 0xbe00, 0xb400, 0xb180
,	0x9380, 0x9600, 0x9c00, 0x9980, 0x8800, 0x8d80, 0x8780, 0x8200
,	0x8381, 0x8601, 0x8c01, 0x8981, 0x9801, 0x9d81, 0x9781, 0x9201
,	0xb001, 0xb581, 0xbf81, 0xba01, 0xab81, 0xae01, 0xa401, 0xa181
,	0xe001, 0xe581, 0xef81, 0xea01, 0xfb81, 0xfe01, 0xf401, 0xf181
,	0xd381, 0xd601, 0xdc01, 0xd981, 0xc801, 0xcd81, 0xc781, 0xc201
,	0x4001, 0x4581, 0x4f81, 0x4a01, 0x5b81, 0x5e01, 0x5401, 0x5181
,	0x7381, 0x7601, 0x7c01, 0x7981, 0x6801, 0x6d81, 0x6781, 0x6201
,	0x2381, 0x2601, 0x2c01, 0x2981, 0x3801, 0x3d81, 0x3781, 0x3201
,	0x1001, 0x1581, 0x1f81, 0x1a01, 0x0b81, 0x0e01, 0x0401, 0x0181
,	0x0383, 0x0603, 0x0c03, 0x0983, 0x1803, 0x1d83, 0x1783, 0x1203
,	0x3003, 0x3583, 0x3f83, 0x3a03, 0x2b83, 0x2e03, 0x2403, 0x2183
,	0x6003, 0x6583, 0x6f83, 0x6a03, 0x7b83, 0x7e03, 0x7403, 0x7183
,	0x5383, 0x5603, 0x5c03, 0x5983, 0x4803, 0x4d83, 0x4783, 0x4203
,	0xc003, 0xc583, 0xcf83, 0xca03, 0xdb83, 0xde03, 0xd403, 0xd183
,	0xf383, 0xf603, 0xfc03, 0xf983, 0xe803, 0xed83, 0xe783, 0xe203
,	0xa383, 0xa603, 0xac03, 0xa983, 0xb803, 0xbd83, 0xb783, 0xb203
,	0x9003, 0x9583, 0x9f83, 0x9a03, 0x8b83, 0x8e03, 0x8403, 0x8183
,	0x8002, 0x8582, 0x8f82, 0x8a02, 0x9b82, 0x9e02, 0x9402, 0x9182
,	0xb382, 0xb602, 0xbc02, 0xb982, 0xa802, 0xad82, 0xa782, 0xa202
,	0xe382, 0xe602, 0xec02, 0xe982, 0xf802, 0xfd82, 0xf782, 0xf202
,	0xd002, 0xd582, 0xdf82, 0xda02, 0xcb82, 0xce02, 0xc402, 0xc182
,	0x4382, 0x4602, 0x4c02, 0x4982, 0x5802, 0x5d82, 0x5782, 0x5202
,	0x7002, 0x7582, 0x7f82, 0x7a02, 0x6b82, 0x6e02, 0x6402, 0x6182
,	0x2002, 0x2582, 0x2f82, 0x2a02, 0x3b82, 0x3e02, 0x3402, 0x3182
,	0x1382, 0x1602, 0x1c02, 0x1982, 0x0802, 0x0d82, 0x0782, 0x0202
};

// the crc16(CCITT) table
tb_uint16_t const g_crc16_ccitt_table[] = 
{
    0x0000, 0x2110, 0x4220, 0x6330, 0x8440, 0xa550, 0xc660, 0xe770
,	0x0881, 0x2991, 0x4aa1, 0x6bb1, 0x8cc1, 0xadd1, 0xcee1, 0xeff1
,	0x3112, 0x1002, 0x7332, 0x5222, 0xb552, 0x9442, 0xf772, 0xd662
,	0x3993, 0x1883, 0x7bb3, 0x5aa3, 0xbdd3, 0x9cc3, 0xfff3, 0xdee3
,	0x6224, 0x4334, 0x2004, 0x0114, 0xe664, 0xc774, 0xa444, 0x8554
,	0x6aa5, 0x4bb5, 0x2885, 0x0995, 0xeee5, 0xcff5, 0xacc5, 0x8dd5
,	0x5336, 0x7226, 0x1116, 0x3006, 0xd776, 0xf666, 0x9556, 0xb446
,	0x5bb7, 0x7aa7, 0x1997, 0x3887, 0xdff7, 0xfee7, 0x9dd7, 0xbcc7
,	0xc448, 0xe558, 0x8668, 0xa778, 0x4008, 0x6118, 0x0228, 0x2338
,	0xccc9, 0xedd9, 0x8ee9, 0xaff9, 0x4889, 0x6999, 0x0aa9, 0x2bb9
,	0xf55a, 0xd44a, 0xb77a, 0x966a, 0x711a, 0x500a, 0x333a, 0x122a
,	0xfddb, 0xdccb, 0xbffb, 0x9eeb, 0x799b, 0x588b, 0x3bbb, 0x1aab
,	0xa66c, 0x877c, 0xe44c, 0xc55c, 0x222c, 0x033c, 0x600c, 0x411c
,	0xaeed, 0x8ffd, 0xeccd, 0xcddd, 0x2aad, 0x0bbd, 0x688d, 0x499d
,	0x977e, 0xb66e, 0xd55e, 0xf44e, 0x133e, 0x322e, 0x511e, 0x700e
,	0x9fff, 0xbeef, 0xdddf, 0xfccf, 0x1bbf, 0x3aaf, 0x599f, 0x788f
,	0x8891, 0xa981, 0xcab1, 0xeba1, 0x0cd1, 0x2dc1, 0x4ef1, 0x6fe1
,	0x8010, 0xa100, 0xc230, 0xe320, 0x0450, 0x2540, 0x4670, 0x6760
,	0xb983, 0x9893, 0xfba3, 0xdab3, 0x3dc3, 0x1cd3, 0x7fe3, 0x5ef3
,	0xb102, 0x9012, 0xf322, 0xd232, 0x3542, 0x1452, 0x7762, 0x5672
,	0xeab5, 0xcba5, 0xa895, 0x8985, 0x6ef5, 0x4fe5, 0x2cd5, 0x0dc5
,	0xe234, 0xc324, 0xa014, 0x8104, 0x6674, 0x4764, 0x2454, 0x0544
,	0xdba7, 0xfab7, 0x9987, 0xb897, 0x5fe7, 0x7ef7, 0x1dc7, 0x3cd7
,	0xd326, 0xf236, 0x9106, 0xb016, 0x5766, 0x7676, 0x1546, 0x3456
,	0x4cd9, 0x6dc9, 0x0ef9, 0x2fe9, 0xc899, 0xe989, 0x8ab9, 0xaba9
,	0x4458, 0x6548, 0x0678, 0x2768, 0xc018, 0xe108, 0x8238, 0xa328
,	0x7dcb, 0x5cdb, 0x3feb, 0x1efb, 0xf98b, 0xd89b, 0xbbab, 0x9abb
,	0x754a, 0x545a, 0x376a, 0x167a, 0xf10a, 0xd01a, 0xb32a, 0x923a
,	0x2efd, 0x0fed, 0x6cdd, 0x4dcd, 0xaabd, 0x8bad, 0xe89d, 0xc98d
,	0x267c, 0x076c, 0x645c, 0x454c, 0xa23c, 0x832c, 0xe01c, 0xc10c
,	0x1fef, 0x3eff, 0x5dcf, 0x7cdf, 0x9baf, 0xbabf, 0xd98f, 0xf89f
,	0x176e, 0x367e, 0x554e, 0x745e, 0x932e, 0xb23e, 0xd10e, 0xf01e
};

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementation
 */

tb_uint16_t tb_crc16_make(tb_byte_t const* data, tb_size_t size, tb_uint16_t seed)
{
    // check
    tb_assert_and_check_return_val(data, 0);

    // init value
    tb_uint32_t crc = seed;

    // done
    tb_byte_t const*    ie = data + size;
    tb_uint16_t const*  pt = (tb_uint16_t const*)g_crc16_table;
    while (data < ie) crc = pt[((tb_uint8_t)crc) ^ *data++] ^ (crc >> 8);

    // ok?
    return (tb_uint16_t)crc;
}
tb_uint16_t tb_crc16_make_from_cstr(tb_char_t const* cstr, tb_uint16_t seed)
{
    // check
    tb_assert_and_check_return_val(cstr, 0);

    // make it
    return tb_crc16_make((tb_byte_t const*)cstr, tb_strlen(cstr) + 1, seed);
}
tb_uint16_t tb_crc16_ccitt_make(tb_byte_t const* data, tb_size_t size, tb_uint16_t seed)
{
    // check
    tb_assert_and_check_return_val(data, 0);

    // init value
    tb_uint16_t crc = seed;

    // done
    tb_byte_t const*    ie = data + size;
    tb_uint16_t const*  pt = (tb_uint16_t const*)g_crc16_ccitt_table;
    while (data < ie) crc = pt[((tb_uint8_t)crc) ^ *data++] ^ (crc >> 8);

    // ok?
    return crc;
}
tb_uint16_t tb_crc16_ccitt_make_from_cstr(tb_char_t const* cstr, tb_uint16_t seed)
{
    // check
    tb_assert_and_check_return_val(cstr, 0);

    // make it
    return tb_crc16_ccitt_make((tb_byte_t const*)cstr, tb_strlen(cstr) + 1, seed);
}
