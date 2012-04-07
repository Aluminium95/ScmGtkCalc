/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * callbacks.c
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
#include "callbacks.h"


/**
 * identifier:
 *
 * documentation ...
 *
 * # Sub heading #
 *
 * more documentation:
 * - list item 1
 * - list item 2
 *
 * Even more docs.
 */
void
destroy (GtkWidget *widget, gpointer data)
{
	gtk_main_quit ();
}

/**
 * Ajoute un espace 
 */
void 
cb_add_space (GtkButton *b, gpointer user)
{
	const ScmCalc* self = SCM_CALC (user);
	
	gint pos = gtk_editable_get_position (GTK_EDITABLE (self->code));

	gtk_editable_insert_text (GTK_EDITABLE (self->code), " ", -1, &pos);

	gtk_editable_set_position (GTK_EDITABLE (self->code), pos);
}

/**
 * Affiche un nombre 
 */
void 
cb_nombre (GtkButton *b, gpointer user_data) 
{
	const ScmCalc* self = SCM_CALC (user_data);
	
	gint pos = gtk_editable_get_position (GTK_EDITABLE (self->code));
	gchar* cmd = g_strdup_printf ("%s", gtk_button_get_label (b));
	gtk_editable_insert_text (GTK_EDITABLE (self->code), cmd, -1, &pos);
	gtk_editable_set_position (GTK_EDITABLE (self->code), pos);
	g_free (cmd);
}

void 
cb_suppr (GtkButton *b, gpointer user_data) 
{
	const ScmCalc* self = SCM_CALC (user_data);
	GtkEntryBuffer* buf = gtk_entry_get_buffer (self->code);
	
	gint pos = gtk_editable_get_position (GTK_EDITABLE (self->code));
	gtk_entry_buffer_delete_text (buf, pos - 1, pos);
	gtk_editable_set_position (GTK_EDITABLE (self->code), pos - 1);
}

void 
cb_to_inexact (GtkButton* b, gpointer user_data) 
{
	ScmCalc* self = SCM_CALC (user_data);
	scmcalc_execute (self, "(exact->inexact (precedent))");
}

void 
cb_to_exact (GtkButton *b, gpointer user_data)
{
	ScmCalc* self = SCM_CALC (user_data);
	scmcalc_execute (self, "(inexact->exact (precedent))");
}

void 
cb_point (GtkButton *b, gpointer user_data) 
{
	const ScmCalc* self = SCM_CALC (user_data);
	
	gint pos = gtk_editable_get_position (GTK_EDITABLE (self->code));
	gtk_editable_insert_text (GTK_EDITABLE (self->code), ".", -1, &pos);
	gtk_editable_set_position (GTK_EDITABLE (self->code), pos);
}

/**
 * Execute la commande
 */
void
cb_executer (GtkButton* b, gpointer user_data) 
{
	ScmCalc* self = SCM_CALC (user_data);
	
	scmcalc_execute_save (self, gtk_entry_get_text (self->code));
	
	gtk_entry_set_text (self->code, "");
}

void cb_precedent (GtkButton* b, gpointer user_data)
{
	ScmCalc* self = SCM_CALC (user_data);
	scmcalc_disp (self,_("precedent"));
	
	gint pos = gtk_editable_get_position (GTK_EDITABLE (self->code));
	gtk_editable_set_position (GTK_EDITABLE (self->code), pos + 1);
}

void cb_multiplier (GtkButton* b, gpointer user_data)
{
	ScmCalc* self = SCM_CALC (user_data);
	scmcalc_disp (self, "* ");
}

void cb_diviser (GtkButton* b, gpointer user_data)
{
	ScmCalc* self = SCM_CALC (user_data);
	scmcalc_disp (self, "/ ");
}

void cb_plus (GtkButton* b, gpointer user_data)
{
	ScmCalc* self = SCM_CALC (user_data);
	scmcalc_disp (self, "+ ");
}

void cb_moins (GtkButton* b, gpointer user_data)
{
	ScmCalc* self = SCM_CALC (user_data);
	scmcalc_disp (self, "- ");
}

void cb_expt (GtkButton* b, gpointer user_data)
{
	ScmCalc* self = SCM_CALC (user_data);
	scmcalc_disp (self, "expt ");
}

void cb_log (GtkButton* b, gpointer user_data)
{
	ScmCalc* self = SCM_CALC (user_data);
	scmcalc_disp (self, "log ");
}

void cb_square (GtkButton* b, gpointer user_data)
{
	ScmCalc* self = SCM_CALC (user_data);
	scmcalc_disp (self, "carre ");
}

void cb_sqrt (GtkButton* b, gpointer user_data)
{
	ScmCalc* self = SCM_CALC (user_data);
	scmcalc_disp (self, "sqrt ");
}

void cb_sinus (GtkButton* b, gpointer user_data)
{
	ScmCalc* self = SCM_CALC (user_data);
	scmcalc_disp (self, "sin ");
}

void cb_cosinus (GtkButton* b, gpointer user_data)
{
	ScmCalc* self = SCM_CALC (user_data);
	scmcalc_disp (self, "cos ");
}

void cb_tan (GtkButton* b, gpointer user_data)
{
	ScmCalc* self = SCM_CALC (user_data);
	scmcalc_disp (self, "tan ");
}

void cb_asinus (GtkButton* b, gpointer user_data)
{
	ScmCalc* self = SCM_CALC (user_data);
	scmcalc_disp (self, "asin ");
}

void cb_acosinus (GtkButton* b, gpointer user_data)
{
	ScmCalc* self = SCM_CALC (user_data);
	scmcalc_disp (self, "acos ");
}

void cb_atan (GtkButton* b, gpointer user_data)
{
	ScmCalc* self = SCM_CALC (user_data);
	scmcalc_disp (self, "atan ");
}

void cb_pi (GtkButton* b, gpointer user_data)
{
	ScmCalc* self = SCM_CALC (user_data);
	scmcalc_disp (self, "pi");
	gint pos = gtk_editable_get_position (GTK_EDITABLE (self->code));
	gtk_editable_set_position (GTK_EDITABLE (self->code), pos + 1);
}
