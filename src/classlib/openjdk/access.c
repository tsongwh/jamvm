/*
 * Copyright (C) 2010, 2012, 2013 Robert Lougher <rob@jamvm.org.uk>.
 *
 * This file is part of JamVM.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "jam.h"
#include "symbol.h"

static Class *magic_accessor;

#ifdef JSR292
static Class *magic_lambda;
#endif

int classlibInitialiseAccess() {
    magic_accessor = findSystemClass0(SYMBOL(sun_reflect_MagicAccessorImpl));
    if(magic_accessor == NULL)
        return FALSE;

#ifdef JSR292
    magic_lambda = findSystemClass0(SYMBOL(java_lang_invoke_MagicLambdaImpl));
    if(magic_lambda == NULL)
        return FALSE;

    registerStaticClassRef(&magic_lambda);
#endif

    registerStaticClassRef(&magic_accessor);
    return TRUE;
}

int classlibAccessCheck(Class *class, Class *referrer) {
#ifdef JSR292
    if(isSubClassOf(magic_lambda, referrer))
        return TRUE;
#endif

    return isSubClassOf(magic_accessor, referrer);
}

