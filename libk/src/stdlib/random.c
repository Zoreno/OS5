/* random.c --- 
 * 
 * Filename: random.c
 * Description: 
 * Author: Joakim Bertils
 * Maintainer: 
 * Created: Sat Feb 10 00:55:57 2018 (+0100)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Sat Feb 10 00:56:33 2018 (+0100)
 *           By: Joakim Bertils
 *     Update #: 2
 * URL: 
 * Doc URL: 
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change Log:
 * 
 * 
 */

/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Emacs.  If not, see <https://www.gnu.org/licenses/>.
 */

/* Code: */




/**
 * @file    random.c
 * @author  Joakim Bertils
 * @date    2017-07-25
 * @brief   Implementation of standard random functions
 */

#include <stdlib.h>
#include <stdint.h>

static uint64_t _seed;

// TODO: Implement proper random machine such as a mersenne twister.
int rand(void)
{
    _seed = UINT64_C(6364136223846793005)*_seed + 1;

    return _seed>>33;
}

int rand_range(int min, int max)
{
    int range = max - min;

    return (rand() % range) + min;
}

void srand(unsigned int seed)
{
    _seed = seed - 1;
}

/* random.c ends here */
