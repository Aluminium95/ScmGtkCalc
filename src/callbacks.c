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


/* Called when the window is closed */
void
destroy (GtkWidget *widget, gpointer data)
{
	gtk_main_quit ();
}


void 
disp_action (const gchar* action, const ScmCalc *self)
{
	
	gchar* cmd = g_strdup_printf("(%s )", action);
	
	gint pos = gtk_editable_get_position (GTK_EDITABLE (self->code));

	gtk_editable_insert_text (GTK_EDITABLE (self->code), cmd, -1, &pos);

	gtk_editable_set_position (GTK_EDITABLE (self->code), pos - 1);

	g_free (cmd);
}

void 
add_space (GObject *b, gpointer user)
{
	const ScmCalc* self = SCM_CALC (user);
	
	gint pos = gtk_editable_get_position (GTK_EDITABLE (self->code));

	gtk_editable_insert_text (GTK_EDITABLE (self->code), " ", -1, &pos);

	gtk_editable_set_position (GTK_EDITABLE (self->code), pos);
}

void 
on_action_clicked (GtkButton* b, gpointer user_data) 
{
	const ScmCalc* self = SCM_CALC (user_data);
	const gchar* action = gtk_button_get_label (b);
	disp_action (action,self);
}

void 
on_single_action_clicked (GtkButton* b, gpointer data) 
{
	const ScmCalc* self = SCM_CALC (data);
	const gchar* action = gtk_button_get_label (b);
	
	gint pos = gtk_editable_get_position (GTK_EDITABLE (self->code));
	
	gchar* cmd = g_strdup_printf ("(%s)", action);
	
	gtk_editable_insert_text (GTK_EDITABLE (self->code), cmd, -1, &pos);
	gtk_editable_set_position (GTK_EDITABLE (self->code), pos);
	
	g_free (cmd);
}

void 
nombre_cb (GtkButton *b, gpointer user_data) 
{
	const ScmCalc* self = SCM_CALC (user_data);
	
	gint pos = gtk_editable_get_position (GTK_EDITABLE (self->code));
	gchar* cmd = g_strdup_printf ("%s", gtk_button_get_label (b));
	gtk_editable_insert_text (GTK_EDITABLE (self->code), cmd, -1, &pos);
	gtk_editable_set_position (GTK_EDITABLE (self->code), pos);
	g_free (cmd);
}

void
on_valider_clicked (GObject* b, gpointer user_data) 
{
	const ScmCalc* self = SCM_CALC (user_data);
	
	execute_action (gtk_entry_get_text (self->code), self);
	
	gtk_entry_set_text (self->code, "");
}

void 
execute_action (const gchar *action, const ScmCalc* self) 
{
	SCM result;
	SCM rep;
	
	// ScmCalc* self_mod = self;

	gtk_label_set_label (self->prec_cmd, action);

	result = scm_c_eval_string (action);
	
	if (scm_is_number (result)) {
		rep = result;

		SCM t = scm_number_to_string (rep, scm_from_int (10));
	
		gtk_label_set_label (self->sortie, scm_to_locale_string (t));
		
		scm_c_define ("private-preced-var", rep);
	}

	gint lines = gtk_text_buffer_get_line_count (self->historique);

	GtkTextIter iter, start, end;
	
	if (lines >= 10) {
		gtk_text_buffer_get_iter_at_line (self->historique, &start, 0);
		gtk_text_buffer_get_iter_at_line (self->historique, &end, 1);
		gtk_text_buffer_delete (self->historique, &start, &end);
	}

	gtk_text_buffer_get_iter_at_line (self->historique, &iter, lines);
	
	gtk_text_buffer_insert (self->historique, &iter, gtk_entry_get_text(self->code), -1);

	gtk_text_buffer_insert (self->historique, &iter, "\n", -1);
}

