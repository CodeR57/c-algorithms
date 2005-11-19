 
/*
 
Copyright (c) 2005, Simon Howard
All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions 
are met:

 * Redistributions of source code must retain the above copyright 
   notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright 
   notice, this list of conditions and the following disclaimer in 
   the documentation and/or other materials provided with the 
   distribution.
 * Neither the name of the C Algorithms project nor the names of its 
   contributors may be used to endorse or promote products derived 
   from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN 
ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
POSSIBILITY OF SUCH DAMAGE.

*/

/* ArrayList test cases */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "arraylist.h"

int variable1, variable2, variable3, variable4;

ArrayList *generate_arraylist(void)
{
    ArrayList *arraylist;
    int i;

    arraylist = arraylist_new(0);

    for (i=0; i<4; ++i) {
        arraylist_append(arraylist, &variable1);
        arraylist_append(arraylist, &variable2);
        arraylist_append(arraylist, &variable3);
        arraylist_append(arraylist, &variable4);
    }

    return arraylist;
}

void test_arraylist_new(void)
{
    arraylist_new(0);
    arraylist_new(-1);
    arraylist_new(10);
}

void test_arraylist_free(void)
{
    ArrayList *arraylist;
    
    arraylist = arraylist_new(0);
    arraylist_free(arraylist);

    /* Test freeing a NULL ArrayList */

    arraylist_free(NULL);
}

void test_arraylist_append(void)
{
    ArrayList *arraylist;
    int i;

    arraylist = arraylist_new(0);

    assert(arraylist->length == 0);

    /* Append some entries */

    arraylist_append(arraylist, &variable1);
    assert(arraylist->length == 1);

    arraylist_append(arraylist, &variable2);
    assert(arraylist->length == 2);

    arraylist_append(arraylist, &variable3);
    assert(arraylist->length == 3);

    arraylist_append(arraylist, &variable4);
    assert(arraylist->length == 4);

    assert(arraylist->data[0] == &variable1);
    assert(arraylist->data[1] == &variable2);
    assert(arraylist->data[2] == &variable3);
    assert(arraylist->data[3] == &variable4);

    /* Test appending many entries */

    for (i=0; i<10000; ++i) {
        arraylist_append(arraylist, NULL);
    }
}


void test_arraylist_prepend(void)
{
    ArrayList *arraylist;
    int i;

    arraylist = arraylist_new(0);

    assert(arraylist->length == 0);

    /* Append some entries */

    arraylist_prepend(arraylist, &variable1);
    assert(arraylist->length == 1);

    arraylist_prepend(arraylist, &variable2);
    assert(arraylist->length == 2);

    arraylist_prepend(arraylist, &variable3);
    assert(arraylist->length == 3);

    arraylist_prepend(arraylist, &variable4);
    assert(arraylist->length == 4);

    assert(arraylist->data[0] == &variable4);
    assert(arraylist->data[1] == &variable3);
    assert(arraylist->data[2] == &variable2);
    assert(arraylist->data[3] == &variable1);

    /* Test prepending many entries */

    for (i=0; i<10000; ++i) {
        arraylist_prepend(arraylist, NULL);
    }
}

void test_arraylist_insert(void)
{
    ArrayList *arraylist;
    int i;

    arraylist = generate_arraylist();

    /* Insert a new entry at index 5 */

    assert(arraylist->length == 16);
    assert(arraylist->data[4] == &variable1);
    assert(arraylist->data[5] == &variable2);
    assert(arraylist->data[6] == &variable3);

    arraylist_insert(arraylist, 5, &variable4);

    assert(arraylist->length == 17);
    assert(arraylist->data[4] == &variable1);
    assert(arraylist->data[5] == &variable4);
    assert(arraylist->data[6] == &variable2);
    assert(arraylist->data[7] == &variable3);

    /* Inserting at the start */

    assert(arraylist->data[0] == &variable1);
    assert(arraylist->data[1] == &variable2);
    assert(arraylist->data[2] == &variable3);

    arraylist_insert(arraylist, 0, &variable4);

    assert(arraylist->length == 18);
    assert(arraylist->data[0] == &variable4);
    assert(arraylist->data[1] == &variable1);
    assert(arraylist->data[2] == &variable2);
    assert(arraylist->data[3] == &variable3);

    /* Inserting at the end */

    assert(arraylist->data[15] == &variable2);
    assert(arraylist->data[16] == &variable3);
    assert(arraylist->data[17] == &variable4);

    arraylist_insert(arraylist, 18, &variable1);

    assert(arraylist->length == 19);
    assert(arraylist->data[15] == &variable2);
    assert(arraylist->data[16] == &variable3);
    assert(arraylist->data[17] == &variable4);
    assert(arraylist->data[18] == &variable1);

    /* Test inserting many entries */

    for (i=0; i<10000; ++i) {
        arraylist_insert(arraylist, 10, &variable1);
    }
}

void test_arraylist_remove_range(void)
{
    ArrayList *arraylist;

    arraylist = generate_arraylist();

    assert(arraylist->length == 16);
    assert(arraylist->data[3] == &variable4);
    assert(arraylist->data[4] == &variable1);
    assert(arraylist->data[5] == &variable2);
    assert(arraylist->data[6] == &variable3);

    arraylist_remove_range(arraylist, 4, 3);

    assert(arraylist->length == 13);
    assert(arraylist->data[3] == &variable4);
    assert(arraylist->data[4] == &variable4);
    assert(arraylist->data[5] == &variable1);
    assert(arraylist->data[6] == &variable2);

    /* Try some invalid ones and check they don't do anything */

    arraylist_remove_range(arraylist, 10, 10);
    arraylist_remove_range(arraylist, -1, 10);
    arraylist_remove_range(arraylist, 0, 16);
    arraylist_remove_range(arraylist, 0, -1);

    assert(arraylist->length == 13);
}

void test_arraylist_remove(void)
{
    ArrayList *arraylist;

    arraylist = generate_arraylist();

    assert(arraylist->length == 16);
    assert(arraylist->data[3] == &variable4);
    assert(arraylist->data[4] == &variable1);
    assert(arraylist->data[5] == &variable2);
    assert(arraylist->data[6] == &variable3);

    arraylist_remove(arraylist, 4);

    assert(arraylist->length == 15);
    assert(arraylist->data[3] == &variable4);
    assert(arraylist->data[4] == &variable2);
    assert(arraylist->data[5] == &variable3);
    assert(arraylist->data[6] == &variable4);

    /* Try some invalid removes */

    arraylist_remove(arraylist, -1);
    arraylist_remove(arraylist, 15);

    assert(arraylist->length == 15);

}

int main(int argc, char *argv[])
{
    test_arraylist_new();
    test_arraylist_free();
    test_arraylist_append();
    test_arraylist_prepend();
    test_arraylist_insert();
    test_arraylist_remove();
    test_arraylist_remove_range();
}
