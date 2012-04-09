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
 * destroy:
 *
 * Callback quand la fenêtre est fermée
 */
void
destroy (GtkWidget *widget, gpointer data)
{
	gtk_main_quit ();
}

/**
 * cb_about_dialog:
 * 
 * Callback qui crée la fenêtre About de la calculette
 */
void 
cb_about_dialog (GtkWidget *widget, gpointer data)
{
	gchar* authors[2] = {"LOPEZ Aliaume <lopezaliaume@gmail.com>", NULL};
	
	gchar* documenters[2] = {"No ... ", NULL};
	gchar* traducteurs = "No ...";
	
	gtk_show_about_dialog (GTK_WINDOW (SCM_CALC(data)->window),
                       "program-name", "GtkCalc",
                       "logo", gdk_pixbuf_new_from_file (DATA "/icon.png", NULL),
                       "title", _("About GtkCalc"),
                       "comments", "Une méga calculatrice programmable en Scheme !",
                       "license", "\n ScmCalcGtk is free software: you can redistribute it and/or modify it \n under the terms of the GNU General Public License as published by the \n Free Software Foundation, either version 3 of the License, or \n (at your option) any later version. \n \n ScmCalcGtk is distributed in the hope that it will be useful, but \n WITHOUT ANY WARRANTY; without even the implied warranty of \n MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. \n See the GNU General Public License for more details. \n \n You should have received a copy of the GNU General Public License along \n with this program.  If not, see <http://www.gnu.org/licenses/>. \n",
                       "copyright", "Copyright (C) 2012 Babakask <lopezaliaume@gmail.com>",
                       "authors", authors,
                       "documenters", documenters,
                       "translator-credits", traducteurs,
                       NULL);
}



/**
 * Ajoute un espace 
 */
void 
cb_add_space (GtkButton *b, gpointer user)
{
	ScmCalc* self = SCM_CALC (user);
	
	scmcalc_disp_string (self, " ");
}

/**
 * Affiche un nombre 
 */
void 
cb_nombre (GtkButton *b, gpointer user_data) 
{
	ScmCalc* self = SCM_CALC (user_data);
	gchar* cmd = g_strdup_printf ("%s", gtk_button_get_label (b));
	
	scmcalc_disp_string (self, cmd);
	
	g_free (cmd);
}

void 
cb_suppr (GtkButton *b, gpointer user_data) 
{
	const ScmCalc* self = SCM_CALC (user_data);
	GtkTextBuffer* buf = gtk_text_view_get_buffer (self->code);
	GtkTextMark* mark_insert = gtk_text_buffer_get_insert (buf);
	GtkTextIter pos;
	gtk_text_buffer_get_iter_at_mark (buf, &pos, mark_insert);
	gtk_text_buffer_backspace (buf, &pos, TRUE, TRUE);
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
	ScmCalc* self = SCM_CALC (user_data);
	
	scmcalc_disp_string (self, ".");
}

/**
 * Execute la commande (n'importe quel objet peut le demander)
 */
void
cb_executer (GObject* b, gpointer user_data) 
{
	ScmCalc* self = SCM_CALC (user_data);
	GtkTextBuffer* buf = gtk_text_view_get_buffer (self->code);
	GtkTextIter start, end;
	
	gtk_text_buffer_get_start_iter (buf, &start);
	gtk_text_buffer_get_end_iter (buf, &end);
	
	const gchar* text = gtk_text_buffer_get_text (buf, &start, &end, FALSE);
	
	if (*text != 0) { // Quand le premier carac n'est pas null
		scmcalc_execute_save (self, text);
		gtk_text_buffer_set_text (buf, "", -1);
	}
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
	scmcalc_disp_string (self, "(pi) ");
}
