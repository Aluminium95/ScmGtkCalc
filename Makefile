PROGRAM = gtkcalc

DOC_MODULE=gtkcalc

# Sources Files
SRC = 	"src"/*.c 

# Paquets
PAQUETS = 	guile-1.8 \
			glib-2.0 \
			gtk+-3.0 \
			gmodule-export-2.0 \
			gobject-2.0
			
PKGS = `pkg-config --cflags --libs $(PAQUETS)`

# Configuration normale
CONFIG = -DDATA=\"`pwd`/Data\" \
		 -DUI_FILE=\"`pwd`/Data/calc.ui\"

# Configuration pour l'installation
CONFIG_INSTALL = -DDATA=\"/usr/share/$(PROGRAM)/Data\" \
				 -DUI_FILE=\"/usr/share/$(PROGRAM)/Data/calc.ui\"

# Arguments du compilateur
OPTS = -g

# Commande du compilateur
CC = gcc

.PHONY : clean
clean:
	@rm -v -fr src/*~ src/*.o
	

# Cible basique
.PHONY : all
all:
	gtkdoc-scan --module=$(DOC_MODULE) --source-dir=./src --output-dir=Doc
	# gtkdoc-scangobj --module=$(DOC_MODULE) 
	cd Doc && gtkdoc-mkdb --module=$(DOC_MODULE) --output-format=xml && cd html && gtkdoc-mkhtml $(DOC_MODULE) ../$(DOC_MODULE)-docs.xml && cd .. &&  gtkdoc-fixxref --module=$(DOC_MODULE) --module-dir=html
	
	$(CC) $(OPTS) $(SRC) -o Build/$(PROGRAM) $(PKGS) $(CONFIG)
	
.PHONY : static
static:
	$(CC) -static --enable-static-link --disable-shared $(OPTS) $(SRC) -o Build/$(PROGRAM) $(PKGS) $(CONFIG)

# Installe sur le système !
.PHONY : install
install : clean
	@rm -v -fr $(PROGRAM)
	# Compilation du programme
	$(CC) $(OPTS) $(SRC) -o Build/$(PROGRAM) $(PKGS) $(CONFIG_INSTALL)
	
	# Création du répertoire du programme
	@mkdir -p "/usr/share/$(PROGRAM)"
	
	# Copie des données du programme
	@cp -R ./Data/ "/usr/share/$(PROGRAM)/Data"
	
	# Modification des permissions des fichiers 
	@chmod -R u+rw "/usr/share/$(PROGRAM)"
	
	# Installation du .desktop
	@cp `pwd`/DesktopIntegration/$(PROGRAM).desktop "/usr/share/applications/$(PROGRAM).desktop"
	@chmod u+x "/usr/share/applications/$(PROGRAM).desktop"
	
	# Installation des icones
	@cp `pwd`/DesktopIntegration/48.png "/usr/share/icons/hicolor/48x48/apps/$(PROGRAM).png"
	@cp `pwd`/DesktopIntegration/64.png "/usr/share/icons/hicolor/64x64/apps/$(PROGRAM).png"
	@cp `pwd`/DesktopIntegration/128.png "/usr/share/icons/hicolor/128x128/apps/$(PROGRAM).png"
	@cp `pwd`/DesktopIntegration/Icon.svg "/usr/share/icons/hicolor/scalable/apps/$(PROGRAM).svg"
	
	# Installation de la man page
	@cp `pwd`/DesktopIntegration/$(PROGRAM).6.gz "/usr/share/man/man6/$(PROGRAM).6.gz"
	
	# Déplacement du programme dans /usr/bin
	@mv Build/$(PROGRAM) "/usr/bin/$(PROGRAM)"
	
# Désinstalle
.PHONY : uninstall
uninstall: clean
	# Supression des données du programme
	@rm -v -fr -r "/usr/share/$(PROGRAM)"
	
	# Supression du programme lui même
	@rm -v -fr "/usr/bin/$(PROGRAM)"
	
	# Supression de l'intégration au desktop
	@rm -v -fr "/usr/share/applications/$(PROGRAM).desktop"
	@rm -v -fr "/usr/share/icons/hicolor/48x48/apps/$(PROGRAM).png"
	@rm -v -fr "/usr/share/icons/hicolor/64x64/apps/$(PROGRAM).png"
	@rm -v -fr "/usr/share/icons/hicolor/128x128/apps/$(PROGRAM).png"
	@rm -v -fr "/usr/share/icons/hicolor/scalable/apps/$(PROGRAM).svg"
	@rm -v -fr "/usr/share/man/man6/$(PROGRAM).6.gz"
	
	@echo "Désinstallé avec succès"

