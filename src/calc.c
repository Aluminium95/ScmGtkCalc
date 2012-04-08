/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * calc.c
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
#include "calc.h"

/**
 * Définition du type pour GType
 */
G_DEFINE_TYPE (ScmCalc, scmcalc, G_TYPE_OBJECT)

static void scmcalc_finalize (GObject *self);
static void scmcalc_class_init (ScmCalcClass* klass);
static void scmcalc_init (ScmCalc* self);
static GtkWidget* scmcalc_create_window (ScmCalc *self);
static SCM wrapper_body_proc (gpointer data);
static SCM wrapper_handler_proc (gpointer data, SCM key, SCM param);

/**
 * scmcalc_class_init:
 * @klass : #ScmCalcClass
 *
 * Initialise la classe  
 *
 */
static void
scmcalc_class_init (ScmCalcClass *klass) 
{
	GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
	gobject_class->finalize = scmcalc_finalize;
	g_return_if_fail (klass != NULL);
}

/**
 * scmcalc_init:
 * @self : Un objet #ScmCalc qui va être initialisé
 *
 * Initialise l'objet
 */
static void
scmcalc_init (ScmCalc *self) 
{
	scm_init_guile ();
	
	scm_c_define_gsubr ("carre", 1, 0, 0, scm_carre);
	
	/*
	 * Chargement :
	 *		- dictionnaire
	 * 		- suites
	 * 		- conversions 
	 *		- operations 
	 */
	scm_c_primitive_load (DATA "/Scheme/utils.scm");
	scm_c_primitive_load (DATA "/Scheme/dico.scm");
	scm_c_primitive_load (DATA "/Scheme/suites.scm");
	scm_c_primitive_load (DATA "/Scheme/convertions.scm");
	scm_c_primitive_load (DATA "/Scheme/operations.scm");
	
	self->window = scmcalc_create_window (self);
	
	gtk_widget_show (self->window);
	
	g_return_if_fail (self != NULL);
}

/**
 * scmcalc_finalize:
 * @self_object
 *
 * Détruit l'objet
 * 
 */
static void 
scmcalc_finalize (GObject *self_object)
{
	ScmCalc* self = SCM_CALC (self_object);
	
}

/**
 * scmcalc_new:
 *
 * Creates a newly allocated ScmCalc
 *
 * Returns: #ScmCalc*
 */
ScmCalc*
scmcalc_new ()
{
	g_type_init ();
	return g_object_new (TYPE_SCM_CALC, NULL);
}

/**
 * scmcalc_free:
 * @scmcalc: the #ScmCalc to delete, can be NULL
 *
 * Deletes a #ScmCalc
 *
 */
void 
scmcalc_free (ScmCalc* scmcalc)
{
	if (scmcalc != NULL) {
		g_object_unref (scmcalc);
		scmcalc = NULL;
	}
}

/**
 * scmcalc_create_window:
 * @self : le #ScmCalc qui doit recevoir la nouvelle fenêtre
 *
 * Crée une nouvelle fenêtre et met à jour les attributs du #ScmCalc 
 * en conséquence.
 *
 * Returns: Une GtkWidget (window) fraîchement allouée :D
 */
static GtkWidget*
scmcalc_create_window (ScmCalc *self)
{
	GtkWidget *window;
	GtkBuilder *builder;
	GtkTextView* h;
	GError* error = NULL;
	const gchar *widget_missing = _("Widget \"%s\" is missing in file %s.");

	/* Load UI from file */
	builder = gtk_builder_new ();
	if (!gtk_builder_add_from_file (builder, UI_FILE, &error))
	{
		g_critical (_("Couldn't load builder file: %s"), error->message);
		g_error_free (error);
	}

	/* Auto-connect signal handlers */
	gtk_builder_connect_signals (builder, self);

	/* Get the window object from the ui file */
	window = GTK_WIDGET (gtk_builder_get_object (builder, "window"));
        if (!window)
        {
                g_critical ( widget_missing,
				"window",
				UI_FILE);
		}

	self->sortie = GTK_LABEL (gtk_builder_get_object (builder, "sortie"));
        if (!self->sortie)
        {
                g_critical (widget_missing,
				"sortie",
				UI_FILE);
		}

	self->code = GTK_ENTRY (gtk_builder_get_object (builder, "code"));
        if (!self->code)
        {
                g_critical (widget_missing,
				"code",
				UI_FILE);
		}

	h = GTK_TEXT_VIEW (gtk_builder_get_object (builder, "historique"));
        if (!h)
        {
                g_critical (widget_missing,
				"historique",
				UI_FILE);
		}

	self->prec_cmd = GTK_LABEL (gtk_builder_get_object (builder, "prec_cmd"));
        if (!self->prec_cmd)
        {
                g_critical (widget_missing,
				"prec_cmd",
				UI_FILE);
		}

	self->historique = gtk_text_view_get_buffer (h);

	g_object_unref (builder);
	
	gtk_window_set_icon_from_file (GTK_WINDOW(window), DATA "/icon.png", &error);
	
	if (error != NULL) {
		g_critical (_("Couldn't set application icon : %s !\n"),
				error->message);
	}
	
	return window;
}


/**
 * scmcalc_disp:
 * @self : #ScmCalc to set
 * @action : the string to display (without the parenthesis)
 *
 * Displays the action on the #GtkEntry with parenthesis around
 *
 */
void 
scmcalc_disp (ScmCalc *self, const gchar* action)
{
	
	gchar* cmd = g_strdup_printf("(%s)", action);
	
	gint pos = gtk_editable_get_position (GTK_EDITABLE (self->code));

	gtk_editable_insert_text (GTK_EDITABLE (self->code), cmd, -1, &pos);

	gtk_editable_set_position (GTK_EDITABLE (self->code), pos - 1);

	g_free (cmd);
}


static SCM
wrapper_body_proc (gpointer data)
{
	gchar* cmd = (gchar*) data;
	return scm_c_eval_string (cmd);
}

static SCM
wrapper_handler_proc (gpointer data, SCM key, SCM param)
{
	ScmCalc* self = SCM_CALC (data);
	gtk_label_set_label (self->sortie, "Erreur Syntaxe !");
	return SCM_BOOL_F;
}

/**
 * scmcalc_execute:
 * @self : #ScmCalc to infer with
 * @ation : the action to be executed
 *
 * Execute the action passed
 *
 */
void 
scmcalc_execute (ScmCalc* self, const gchar *action) 
{
	SCM result;
	SCM rep;

	gtk_label_set_label (self->prec_cmd, action);
	
	result = scm_c_catch (SCM_BOOL_T,
                    wrapper_body_proc, (gpointer) action,
                    wrapper_handler_proc, (gpointer) self,
                    NULL, NULL);
	
	if (scm_is_number (result)) {
		rep = result;

		SCM t = scm_number_to_string (rep, scm_from_int (10));
		
		gtk_label_set_label (self->sortie, scm_to_locale_string (t));
		
		SCM append_func_symbol = scm_c_lookup("precedent-add");
 		SCM append_func = scm_variable_ref (append_func_symbol);
		scm_call_1 (append_func, rep);
	} else if (scm_list_p (result) == SCM_BOOL_T) {
		/*SCM elem;
		elem = scm_c_eval_string ("(map )");*/
	}
}

/**
 * scmcalc_execute_save:
 * @self : #ScmCalc to infer
 * @ation : the action to be executed
 *
 * The same as scmcalc_execute() except that it
 * saves the command in the command-history with 
 * scmcalc_add_historique() 
 *
 */
void 
scmcalc_execute_save (ScmCalc* self, const gchar *action)
{
	scmcalc_execute (self, action);
	scmcalc_add_historique (self, action);
}

/**
 * scmcalc_add_historique:
 * @self : #ScmCalc to infer
 * @ation : the action to be saved
 *
 * Saves the command in the command history 
 *
 */
void 
scmcalc_add_historique (ScmCalc* self, const gchar *text)
{
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
