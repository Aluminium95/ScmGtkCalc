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

/**
 * Création de la classe 
 */
static void
scmcalc_class_init (ScmCalcClass *klass) 
{
	GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
	gobject_class->finalize = scmcalc_finalize;
	g_return_if_fail (klass != NULL);
}

/**
 * Création d'un objet
 */
static void
scmcalc_init (ScmCalc *self) 
{
	scm_init_guile ();
	
	scm_c_define_gsubr ("carre", 1, 0, 0, scm_carre);
	
	scm_c_define ("private-preced-var", scm_from_int (0));
	
	scm_c_eval_string ("(define (precedent) private-preced-var)");
	
	self->window = scmcalc_create_window (self);
	
	gtk_widget_show (self->window);
	
	g_return_if_fail (self != NULL);
}

/**
 * Destruction d'un objet
 */
static void 
scmcalc_finalize (GObject *self_object)
{
	ScmCalc* self = SCM_CALC (self_object);
	
}

/** 
 * Retourne un nouvel objet
 */
ScmCalc*
scmcalc_new ()
{
	g_type_init ();
	return g_object_new (TYPE_SCM_CALC, NULL);
}

/**
 * Libère un objet
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
 * Crée la fenetre
 */
static GtkWidget*
scmcalc_create_window (ScmCalc *self)
{
	GtkWidget *window;
	GtkBuilder *builder;
	GtkTextView* h;
	GError* error = NULL;

	/* Load UI from file */
	builder = gtk_builder_new ();
	if (!gtk_builder_add_from_file (builder, UI_FILE, &error))
	{
		g_critical ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}

	/* Auto-connect signal handlers */
	gtk_builder_connect_signals (builder, self);

	/* Get the window object from the ui file */
	window = GTK_WIDGET (gtk_builder_get_object (builder, "window"));
        if (!window)
        {
                g_critical ("Widget \"%s\" is missing in file %s.",
				"window",
				UI_FILE);
		}

	self->sortie = GTK_LABEL (gtk_builder_get_object (builder, "sortie"));
        if (!self->sortie)
        {
                g_critical ("Widget \"%s\" is missing in file %s.",
				"sortie",
				UI_FILE);
		}

	self->code = GTK_ENTRY (gtk_builder_get_object (builder, "code"));
        if (!self->code)
        {
                g_critical ("Widget \"%s\" is missing in file %s.",
				"code",
				UI_FILE);
		}

	h = GTK_TEXT_VIEW (gtk_builder_get_object (builder, "historique"));
        if (!h)
        {
                g_critical ("Widget \"%s\" is missing in file %s.",
				"historique",
				UI_FILE);
		}

	self->prec_cmd = GTK_LABEL (gtk_builder_get_object (builder, "prec_cmd"));
        if (!self->prec_cmd)
        {
                g_critical ("Widget \"%s\" is missing in file %s.",
				"prec_cmd",
				UI_FILE);
		}

	self->historique = gtk_text_view_get_buffer (h);

	g_object_unref (builder);
	
	gtk_window_set_icon_from_file (GTK_WINDOW(window), DATA "/icon.png", &error);
	
	if (error != NULL) {
		g_critical ("Ne peut faire l'icone : %s !\n",
				error->message);
	}
	
	return window;
}

