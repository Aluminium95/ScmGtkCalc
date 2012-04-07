/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * calc.h
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

#ifndef H_CALCULETTE

#define H_CALCULETTE

#include <gtk/gtk.h>
#include <glib-object.h>
#include <glib/gi18n.h>
#include <libguile.h>
#include "scm_functions.h"

#define TYPE_SCM_CALC 				(scmcalc_get_type ())
#define SCM_CALC(obj) 				(G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_SCM_CALC, ScmCalc))
#define IS_SCM_CALC(obj) 			(G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_SCM_CALC))
#define SCM_CALC_CLASS(klass) 		(G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_SCM_CALC, ScmCalcClass))
#define IS_SCM_CALC_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_SCM_CALC))
#define SCM_CALC_GET_CLASS(obj) 	(G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_SCM_CALC, ScmCalcClass))

typedef struct _ScmCalc ScmCalc;
typedef struct _ScmCalcClass ScmCalcClass;

struct _ScmCalc {
	GObject parent;
	GtkWidget *window;
	
	SCM rep;
	
	GtkEntry* code;
	GtkLabel* prec_cmd;
	GtkLabel* sortie;
	GtkTextBuffer* historique;
};

struct _ScmCalcClass {
	GObjectClass parent;
};

GType scmcalc_get_type (void);

/* Méthodes */
ScmCalc* scmcalc_new ();
void scmcalc_free (ScmCalc* scmcalc);
void scmcalc_run (ScmCalc* scmcalc);

#endif /* H_CALCULETTE */
