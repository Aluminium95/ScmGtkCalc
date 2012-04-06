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
 
#ifndef H_CALCULETTE_CB

#define H_CALCULETTE_CB

#include <gtk/gtk.h>
#include <libguile.h>
#include "calc.h"

/* Called when the window is closed */
void destroy (GtkWidget *widget, gpointer data);

void disp_action (const gchar* action, const ScmCalc* self);

void add_space (GObject *b, gpointer user);

void on_action_clicked (GtkButton* b, gpointer user_data);

void on_single_action_clicked (GtkButton* b, gpointer data);

void nombre_cb (GtkButton *b, gpointer user_data);

void on_valider_clicked (GObject* b, gpointer user_data);

void execute_action (const gchar *action, const ScmCalc* self);

#endif /* H_CALCULETTE_CB */
