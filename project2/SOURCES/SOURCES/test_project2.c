/*
 * test_circbuff.c
 *
 *  Created on: Feb 28, 2017
 *      Author: viga7710
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "data.h"
#include "memory.h"
#include "circbuff.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>



uint32_t length = 10;
uint32_t odd_length = 11;
uint8_t set[32]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
uint8_t length_buff = 10;
uint8_t data[11] = {1,2,3,4,5,6,7,8,9,10,11};

void test_big_to_little_invalid(void **state)
{
	uint32_t *ptr = NULL;
	uint32_t length = 4;
	enum data_status status = big_to_little32(ptr,length);
	assert_int_equal(status, INVALID_POINTER);
}

void test_little_to_big_invalid(void **state)
{
	uint32_t *ptr = NULL;
	uint32_t length = 4;
	enum data_status status = little_to_big32(ptr,length);
	assert_int_equal(status, INVALID_POINTER);
}

void test_big_to_little_valid_conversion(void **state)
{
	uint32_t data = 0x12345678;
	uint32_t *ptr = &data;
	uint32_t length = 4;
	enum data_status status = big_to_little32(ptr,length);
	assert_int_equal(status, SUCCESSFUL_CONVERSION);
}

void test_little_to_big_valid_conversion(void **state)
{
	uint32_t data = 0x12345678;
	uint32_t *ptr = &data;
	uint32_t length = 4;
	enum data_status status = little_to_big32(ptr,length);
	assert_int_equal(status, SUCCESSFUL_CONVERSION);
}


void test_memmove_invalid_pointer(void **state)
{
	uint8_t *src = &set[0];
	uint8_t *dst = NULL;
	enum memory_status status = my_memmove(src,dst,length);
	assert_int_equal(status, INVALID_MEMORY_POINTER);
}

void test_memmove_no_overlap(void **state)
{
	uint8_t *src = &set[5];
	uint8_t *dst = &set[20];
	enum memory_status status = my_memmove(src,dst,length);
	assert_int_equal(status, SUCCESSFUL_TRANSFER);
}

void test_memmove_src_in_dst(void **state)
{
	uint8_t *src = &set[15];
	uint8_t *dst = &set[10];
	enum memory_status status = my_memmove(src,dst,length);
	assert_int_equal(status, SUCCESSFUL_TRANSFER);
}

void test_memmove_dst_in_src(void **state)
{
	uint8_t *src = &set[10];
	uint8_t *dst = &set[15];
	enum memory_status status = my_memmove(src,dst,length);
	assert_int_equal(status, SUCCESSFUL_TRANSFER);
}


void test_memset_invalid_pointer(void **state)
{
	uint8_t *src = NULL;
	uint8_t value = 5;
	enum memory_status status = my_memset(src,length,value);
	assert_int_equal(status, INVALID_MEMORY_POINTER);
}

void test_memset_valid(void **state)
{
	uint8_t *src = &set[0];
	uint8_t value = 5;
	enum memory_status status = my_memset(src,length,value);
	assert_int_equal(status, SUCCESSFUL_TRANSFER);
}

void test_memzero_invalid_pointer(void **state)
{
	uint8_t *src = NULL;
	enum memory_status status = my_memzero(src,length);
	assert_int_equal(status, INVALID_MEMORY_POINTER);
}

void test_memzero_valid(void **state)
{
	uint8_t *src = &set[5];
	enum memory_status status = my_memzero(src,length);
	assert_int_equal(status, SUCCESSFUL_TRANSFER);
}

void test_reverse_invalid_pointer(void **state)
{
	uint8_t *src = NULL;
	enum memory_status status = my_reverse(src,length);
	assert_int_equal(status, INVALID_MEMORY_POINTER);
}

void test_reverse_odd(void **state)
{
	uint8_t *src = &set[10];
	enum memory_status status = my_reverse(src,odd_length);
	assert_int_equal(status, SUCCESSFUL_TRANSFER);
}

void test_reverse_even(void **state)
{
	uint8_t *src = &set[10];
	enum memory_status status = my_reverse(src,length);
	assert_int_equal(status, SUCCESSFUL_TRANSFER);
}

void test_reverse_character(void **state)
{
	uint8_t chr_set[256];
	uint8_t chr_check[256];
	uint16_t i;

	for(i=0;i<256;i++)
	{
		chr_set[i] = i;
		chr_check[i] = i;
	}

	uint8_t *src = chr_set;
	enum memory_status status = my_reverse(src,256);

	for(i=0;i<256;i++)
	{
		if(chr_set[i]!=chr_check[255-i])
		{
			status = TRANSFER_FAILED;
			break;
		}
	}

	if(i == 256)
		assert_int_equal(status, SUCCESSFUL_TRANSFER);
	else assert_int_equal(status, TRANSFER_FAILED);
}


void test_circbuf_allocate_free(void **state)
{
	CircBuff *test_buff = (CircBuff *) calloc(1,sizeof(CircBuff));
	cbuff_state status = cbuffer_memoryAllocate(test_buff,length_buff);
	assert_int_equal(status, NO_ERROR);
}

void test_circbuf_invalid_pointer(void **state)
{
	CircBuff *test_buff = (CircBuff *) calloc(1,sizeof(CircBuff));
	cbuff_state status = cbuffer_memoryAllocate(test_buff,0);
	assert_int_not_equal(status, BUFFER_ALLCATION_FAILURE);
}

void test_circbuf_non_initialized_buffer(void **state)
{
	CircBuff *test_buffer = (CircBuff *) calloc(1,sizeof(CircBuff));
	(test_buffer->length) = length_buff;
	cbuff_state status;
	if((test_buffer->head) == NULL || (test_buffer->buffer) == NULL || (test_buffer->tail) == NULL)
		{
			status = ERROR;
		}
	else status = NO_ERROR;
	assert_int_equal(status, ERROR);
}

void test_circbuf_add_remove(void **state)
{
	CircBuff *test_buffer = (CircBuff *) calloc(1,sizeof(CircBuff));
	(test_buffer->length) = length_buff;
	cbuffer_memoryAllocate(test_buffer,length_buff);
	cbuffer_init(test_buffer);	
	cbuffer_add(test_buffer,data,length_buff);
	cbuff_state status = cbuffer_remove(test_buffer,length_buff);
	assert_int_equal(status, NO_ERROR);
}

void test_circbuf_buffer_full(void **state)
{
	CircBuff *test_buffer = (CircBuff *) calloc(1,sizeof(CircBuff));
	cbuffer_memoryAllocate(test_buffer,length_buff);
	(test_buffer->length) = length_buff;
	cbuffer_init(test_buffer);
	cbuffer_add(test_buffer,data,length_buff);
	cbuff_state status = cbuffer_full(test_buffer);
	assert_int_equal(status, BUFFER_FULL);
}

void test_circbuf_buffer_empty(void **state)
{
	CircBuff *test_buffer = (CircBuff *) calloc(1,sizeof(CircBuff));
	cbuffer_memoryAllocate(test_buffer,length_buff);
	(test_buffer->length) = length_buff;
	cbuffer_init(test_buffer);
	cbuff_state status = cbuffer_empty(test_buffer);
	assert_int_equal(status, BUFFER_EMPTY);
}

void test_circbuf_wrap_add(void **state)
{
	CircBuff *test_buffer = (CircBuff *) calloc(1,sizeof(CircBuff));
	cbuffer_memoryAllocate(test_buffer,length_buff);
	(test_buffer->length) = length_buff;
	cbuffer_init(test_buffer);
	uint8_t *last = (uint8_t *)(test_buffer->head);
	cbuffer_add(test_buffer,data,length_buff);
	cbuff_state status;	
	if((test_buffer->head)==last)
		status = NO_ERROR;
	else status = ERROR;

	assert_int_equal(status, NO_ERROR);
}

void test_circbuf_wrap_remove(void **state)
{
	CircBuff *test_buffer = (CircBuff *) calloc(1,sizeof(CircBuff));
	cbuffer_memoryAllocate(test_buffer,length_buff);
	(test_buffer->length) = length_buff;
	cbuffer_init(test_buffer);
	uint8_t *last = (uint8_t *)(test_buffer->tail);
	cbuffer_add(test_buffer,data,length_buff);
	cbuffer_remove(test_buffer,length_buff);
	cbuff_state status;
	if((test_buffer->tail)==last)
		status = NO_ERROR;
	else status = ERROR;

	assert_int_equal(status, NO_ERROR);
}

void test_circbuf_over_fill(void **state)
{
	CircBuff *test_buffer = (CircBuff *) malloc(sizeof(CircBuff));
	cbuffer_memoryAllocate(test_buffer,length_buff);
	(test_buffer->length) = length_buff;
	cbuffer_init(test_buffer);
	cbuff_state status = cbuffer_add(test_buffer,data,length_buff+1);
	assert_int_equal(status, BUFFER_FULL);
}

void test_circbuf_over_empty(void **state)
{
	CircBuff *test_buffer = (CircBuff *) malloc(sizeof(CircBuff));
	cbuffer_memoryAllocate(test_buffer,length_buff);
	(test_buffer->length) = length_buff;
	cbuffer_init(test_buffer);
	cbuff_state status = cbuffer_remove(test_buffer,1);
	assert_int_equal(status, BUFFER_EMPTY);
}

int main(int argc, char **argv)
{
  const struct CMUnitTest tests[] = {
	cmocka_unit_test(test_circbuf_allocate_free),
	cmocka_unit_test(test_circbuf_invalid_pointer),
	cmocka_unit_test(test_circbuf_non_initialized_buffer),
	cmocka_unit_test(test_circbuf_add_remove),
	cmocka_unit_test(test_circbuf_buffer_full),	
	cmocka_unit_test(test_circbuf_buffer_empty),
    cmocka_unit_test(test_circbuf_wrap_add),
    cmocka_unit_test(test_circbuf_wrap_remove),
    cmocka_unit_test(test_circbuf_over_fill),
    cmocka_unit_test(test_circbuf_over_empty),
	cmocka_unit_test(test_big_to_little_invalid),
    cmocka_unit_test(test_little_to_big_invalid),
    cmocka_unit_test(test_big_to_little_valid_conversion),
    cmocka_unit_test(test_little_to_big_valid_conversion),
    cmocka_unit_test(test_memmove_invalid_pointer),
    cmocka_unit_test(test_memmove_no_overlap),	
    cmocka_unit_test(test_memmove_dst_in_src),
    cmocka_unit_test(test_memmove_src_in_dst),
	cmocka_unit_test(test_memset_invalid_pointer),
	cmocka_unit_test(test_memset_valid),
	cmocka_unit_test(test_memzero_invalid_pointer),
	cmocka_unit_test(test_memzero_valid),
	cmocka_unit_test(test_reverse_invalid_pointer),
	cmocka_unit_test(test_reverse_odd),
	cmocka_unit_test(test_reverse_even),
	cmocka_unit_test(test_reverse_character),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
