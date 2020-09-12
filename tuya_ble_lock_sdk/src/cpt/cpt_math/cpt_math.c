#include "app_common.h"




/*********************************************************************
 * LOCAL CONSTANTS
 */

/*********************************************************************
 * LOCAL STRUCT
 */

/*********************************************************************
 * LOCAL VARIABLES
 */

/*********************************************************************
 * LOCAL FUNCTION
 */

/*********************************************************************
 * VARIABLES
 */




/*********************************************************
FN: sum ����
*/
uint8_t cpt_check_sum(uint8_t *buf, uint32_t size)
{
    uint32_t i;
    uint8_t  sum = 0;
    for(i=0; i<size; i++)
    {
        sum += buf[i];
    }
    return sum;
}

/*********************************************************
FN: sum16 ����
*/
uint16_t cpt_check_sum_16(uint8_t *buf, uint32_t size)
{
    uint32_t i;
    uint16_t  sum = 0;
    for(i=0; i<size; i++)
    {
        sum += buf[i];
    }
    return sum;
}

/*********************************************************
FN: crc16 ����
*/
uint16_t cpt_crc16_compute(uint8_t* buf, uint16_t size, uint16_t* p_crc)
{
    uint16_t poly[2] = {0, 0xa001}; //0x8005 <==> 0xa001
    uint16_t crc = 0xffff;
    int i, j;
    
    for(j=size; j>0; j--)
    {
        uint8_t ds = *buf++;
        for(i=0; i<8; i++)
        {
            crc = (crc >> 1) ^ poly[(crc ^ ds) & 1];
            ds = ds >> 1;
        }
    }
    return crc;
}

/*********************************************************
FN: crc32 ����
*/
uint32_t cpt_crc32_compute(uint8_t* buf, uint32_t size, uint32_t* p_crc)
{
    uint32_t crc;

    crc = (p_crc == NULL) ? 0xFFFFFFFF : ~(*p_crc);
    for (uint32_t i = 0; i < size; i++)
    {
        crc = crc ^ buf[i];
        for (uint32_t j = 8; j > 0; j--)
        {
            crc = (crc >> 1) ^ (0xEDB88320U & ((crc & 1) ? 0xFFFFFFFF : 0));
        }
    }
    return ~crc;
}

/*********************************************************
FN: 
*/
void cpt_reverse_byte(void* buf, uint32_t size)
{
    uint8_t* p_tmp = buf;
    uint8_t  tmp;
    for(uint32_t idx=0; idx<size/2; idx++)
    {
        tmp = *(p_tmp+idx);
        *(p_tmp+idx) = *(p_tmp+size-1-idx);
        *(p_tmp+size-1-idx) = tmp;
    }
}

/*********************************************************
FN: 
*/
uint32_t cpt_num_array_2_int(uint8_t *num_array, uint32_t start_idx, uint32_t size)
{
    if(start_idx >= size) {
        return (uint32_t)-1;
    }
    
	uint32_t tmp_int = 0;
	for (uint32_t idx=start_idx; idx<start_idx+size; idx++) {
		tmp_int = (tmp_int*10) + num_array[idx];
	}
	return tmp_int;
}




/*********************************************************  notation conversion  *********************************************************/

/*********************************************************
FN: 
*/
long source_to_decimal(int source_notation, uint8_t source_array[], uint32_t source_array_len)
{
    long decimal_num = 0;
    
    for(int idx=0; idx<source_array_len; idx++) {
        decimal_num = (decimal_num*source_notation) + source_array[idx];
    }
    
    return decimal_num;
}

/*********************************************************
FN: 
*/
int decimal_to_object(long decimal_num, int object_notation, uint8_t object_array[])
{
    int idx=0;
    while(decimal_num) {
        object_array[idx] = decimal_num % object_notation;  /*���������ת��Ϊ�ַ�*/
        decimal_num = decimal_num / object_notation;  /*��ʮ���������Ի���*/
        idx++;
    }
    return idx;
}

/*********************************************************
FN: 
*/
int source_to_object(int source_notation, uint8_t source_array[], uint32_t source_array_len, int object_notation, uint8_t object_array[])
{
    long decimal_num = source_to_decimal(source_notation, source_array, source_array_len);
    int object_array_length = decimal_to_object(decimal_num, object_notation, object_array);
    cpt_reverse_byte(object_array, object_array_length);
    return object_array_length;
}








































