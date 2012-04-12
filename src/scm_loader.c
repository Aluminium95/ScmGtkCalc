/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * scm_loader.c
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
#include "scm_loader.h"

/**
 * wrapper_body_proc:
 *
 * Wrapper pour lancer la fonction de chargement dans un catch
 */
static SCM
wrapper_body_proc (gpointer data)
{
	gchar* cmd = (gchar*) data;
	return scm_c_primitive_load (cmd);
}

/** 
 * wrapper_handler_proc:
 * 
 * Gestionnaire des erreurs de chargement
 */
static SCM
wrapper_handler_proc (gpointer data, SCM key, SCM param)
{
	g_error ("Erreur ... \n");
	return SCM_BOOL_F;
}

/**
 * load_scm_file:
 * @btn : le bouton [inutilisé]
 * @data : [inutilisé]
 *
 * Charge un fichier scm dans l'interprêteur
 * afin que les fonctions soit chargées globalement
 * pour toute la calculette
 */
void
load_scm_file (GtkAction* btn, gpointer data)
{
	GtkFileFilter *filter;
	GtkWidget *chooser;
	gchar *chemin = NULL;
	SCM result;
	
	chooser = gtk_file_chooser_dialog_new ("Ouvrir...",
											GTK_WINDOW(SCM_CALC (data)->window),
											GTK_FILE_CHOOSER_ACTION_OPEN,
											GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
											GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
											NULL);
	
	gtk_window_set_modal(GTK_WINDOW(chooser), TRUE);
		
	filter = gtk_file_filter_new ();
	gtk_file_filter_add_pattern (filter, "*.scm");
	
	gtk_file_chooser_set_filter (GTK_FILE_CHOOSER (chooser), filter);
	
	if (gtk_dialog_run (GTK_DIALOG (chooser)) == GTK_RESPONSE_ACCEPT)
	{
		chemin = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (chooser));
		
		result = scm_c_catch (SCM_BOOL_T,
							wrapper_body_proc, (gpointer) chemin,
							wrapper_handler_proc, NULL,
							NULL, NULL);
		
		g_free (chemin);
	}


	gtk_widget_destroy (chooser);	
}
