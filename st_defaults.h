// Copyright 2024 Guillaume Stordeur <guillaume.stordeur@gmail.com>
// Copyright 2024 Matt Skalecki <ikcelaks@gmail.com>
// Copyright 2024 QKekos <q.kekos.q@gmail.com>
// SPDX-License-Identifier: Apache-2.0
#pragma once

// If the user does not set these in their config.h,
// these values will be used by default.

#ifndef SEQUENCE_TRANSFORM_IDLE_TIMEOUT
#define SEQUENCE_TRANSFORM_IDLE_TIMEOUT 2500
#endif

#ifndef SEQUENCE_TRANSFORM_ENHANCED_BACKSPACE
#define SEQUENCE_TRANSFORM_ENHANCED_BACKSPACE 1
#endif

#ifndef SEQUENCE_TRANSFORM_FALLBACK_BUFFER
#define SEQUENCE_TRANSFORM_FALLBACK_BUFFER 1
#endif

#ifndef SEQUENCE_TRANSFORM_DEBUG
#define SEQUENCE_TRANSFORM_DEBUG 0
#endif

#ifndef SEQUENCE_TRANSFORM_LOG_TIME
#define SEQUENCE_TRANSFORM_LOG_TIME 0
#endif

#ifndef SEQUENCE_TRANSFORM_RULE_SEARCH
#define SEQUENCE_TRANSFORM_RULE_SEARCH 0
#endif

#ifndef SEQUENCE_TRANSFORM_RULE_SEARCH_MAX_SKIP
#define SEQUENCE_TRANSFORM_RULE_SEARCH_MAX_SKIP 4
#endif

#ifndef SEQUENCE_TRANSFORM_RECORD_RULE_USAGE
#define SEQUENCE_TRANSFORM_RECORD_RULE_USAGE 0
#endif

#ifndef SEQUENCE_TRANSFORM_EXTRA_BUFFER
#define SEQUENCE_TRANSFORM_EXTRA_BUFFER 10
#endif

// Disable features that do nothing without print
#ifdef NO_PRINT
#undef  SEQUENCE_TRANSFORM_DEBUG
#define SEQUENCE_TRANSFORM_DEBUG 0

#undef  SEQUENCE_TRANSFORM_LOG_TIME
#define SEQUENCE_TRANSFORM_LOG_TIME 0

#undef  SEQUENCE_TRANSFORM_RECORD_RULE_USAGE
#define SEQUENCE_TRANSFORM_RECORD_RULE_USAGE 0
#endif
