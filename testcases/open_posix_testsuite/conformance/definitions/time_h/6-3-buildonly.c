  /*
 * Copyright (c) 2002, Intel Corporation. All rights reserved.
 * Created by:  julie.n.fleischer REMOVE-THIS AT intel DOT com
 * This file is licensed under the GPL license.  For the full content
 * of this license, see the COPYING file at the top level of this
 * source tree.

  @pt:TMR
  @pt:MON
  Test that CLOCK_MONOTONIC is defined
  */

#include <time.h>

#ifndef CLOCK_MONOTONIC
#error CLOCK_MONOTONIC not defined
#endif
