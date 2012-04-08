/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * scm_functions.c
 * Copyright (C) 2012 Babakask <lopezaliaume@gmail.com>
 * 
 * ScmCalcGtk is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * ScmCalcGtk is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "scm_functions.h"

/**
 * scm_return_rep:
 * 
 * Retourne le dernier résultat,
 * celui-ci étant sauvegardé dans "private-preced-var"
 */
SCM
scm_return_rep ()
{
	return scm_c_lookup ("private-preced-var");
}


/**
 * scm_carre:
 * @nbr : le nombre à élever au carré
 *
 * Returns: @nbr * @nbr 
 */
SCM
scm_carre (SCM nbr) 
{
	return scm_sys_expt (nbr, scm_from_int (2));
}

