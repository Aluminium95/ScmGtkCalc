/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * callbacks.h
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
 
#ifndef _H_CALCULETTE_CB

#define _H_CALCULETTE_CB

#include <gtk/gtk.h>
#include <libguile.h>
#include "calc.h"

/**
 * foo_get_bar:
 * @foo: some foo
 *
 * Retrieves @foo's bar.
 *
 * Returns: @foo's bar
 *
 * Since: 2.6
 * Deprecated: 2.12: Use foo_baz_get_bar() instead.
 **/
void destroy (GtkWidget *widget, gpointer data);

/**
 * Globales
 */
void cb_add_space (GtkButton *b, gpointer user);
void cb_nombre (GtkButton *b, gpointer user_data);
void cb_point (GtkButton *b, gpointer user_data);
void cb_executer (GObject* b, gpointer user_data);
void cb_suppr (GtkButton* b, gpointer user_data);
void cb_to_inexact (GtkButton* b, gpointer user_data);
void cb_to_exact (GtkButton* b, gpointer user_data);
gboolean cb_code_change (GtkWidget * widget, GdkEventKey* pKey,gpointer user_data);

/**
 * Opérations simples (-+/*)
 */
void cb_multiplication (GtkButton* b, gpointer user_data);
void cb_division (GtkButton* b, gpointer user_data);
void cb_plus (GtkButton* b, gpointer user_data);
void cb_moins (GtkButton* b, gpointer user_data);

/**
 * Trigo
 */
void cb_sinus (GtkButton*b, gpointer user_data);
void cb_asinus (GtkButton*b, gpointer user_data);
void cb_cosinus (GtkButton*b, gpointer user_data);
void cb_acosinus (GtkButton*b, gpointer user_data);
void cb_tan (GtkButton*b, gpointer user_data);
void cb_atan (GtkButton*b, gpointer user_data);
void cb_pi (GtkButton*b, gpointer user_data);

/**
 * Powers !
 */
void cb_expt (GtkButton*b, gpointer user_data);
void cb_log (GtkButton*b, gpointer user_data);
void cb_carre (GtkButton*b, gpointer user_data);
void cb_sqrt (GtkButton*b, gpointer user_data);





#endif /* H_CALCULETTE_CB */
