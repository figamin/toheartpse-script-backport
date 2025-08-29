/*
 * LEAF Visual Novel System For X
 * (c) Copyright 1999,2000 Go Watanabe mailto:go@denpa.org
 * All rights reserverd.
 *
 * ORIGINAL LVNS (c) Copyright 1996-1999 LEAF/AQUAPLUS Inc.
 *
 * $Id: leafpack.h,v 1.1 2001/07/25 14:36:49 tf Exp $
 *
 */

#ifndef ___LEAFPAK_H
#define ___LEAFPAK_H

#define LP_KEY_LEN 233

#include <sys/types.h>

typedef enum {
  LPTYPE_SIZUWIN,
  LPTYPE_KIZUWIN,
  LPTYPE_TOHEART,
  LPTYPE_SAORIN,
  LPTYPE_UNKNOWN
} LeafPackType;

/*
 * �ѥå�����
 */
typedef struct {
  LeafPackType type; /*
                      * �ѥå��μ���
                      */

  u_char *addr;        /*
                        * ��Ƭ���ɥ쥹
                        */
  size_t size;         /*
                        * ������
                        */
  int file_num;        /*
                        * �ѥå���Υե������
                        */
  int key[LP_KEY_LEN]; /*
                        * Ÿ���ѥ���
                        */

  /*
   * �ե��������
   */
  struct LeafFileInfo {
    char name[13]; /*
                    * �ե�����̾
                    */
    off_t pos;     /*
                    * �ե��������Ƭ����Υ��ե��å�
                    */
    size_t len;    /*
                    * �ե�����Υ�����
                    */
  } * files;

} LeafPack;

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

extern LeafPack *leafpack_new(const char *packname);
extern void leafpack_delete(LeafPack *);

extern void leafpack_print_type(LeafPack *);
extern void leafpack_print_table(LeafPack *, int verbose);

extern int leafpack_find(LeafPack *p, const char *name);
extern u_char *leafpack_extract(LeafPack *p, int index, size_t *sizeret);

void leafpack_lzs(const u_char *loadBuf, u_char *saveBuf, size_t size);
void leafpack_lzs2(const u_char *loadBuf, u_char *saveBuf, size_t size);
void leafpack_lzs3(const u_char *loadBuf, u_char *saveBuf, size_t size);

#endif
