; Gestion du Dictionnaire
; Entièrement fait main !
; Youhou !

; Crée un dico
(define (dict-new)
	'())

; Vérifie que le dico contient
; la clef
; Complexité : O(N)
(define (dict-contains? dict key)
	(cond
		((equal? dict '())
			#f)
		((equal? key (car (car dict)))
			#t)
		(else
			(dict-contains? (cdr dict) key))))

; Renvoie la valeur associée
; Complexité : O(N)
(define (dict-get dict key)
	(cond 
		((equal? dict '())
			'(error "Not Found"))
		((equal? key (car (car dict)))
			(cdr (car dict)))
		(else
			(dict-get (cdr dict) key))))

; Renvoie le dico avec un couple de valeurs
; en plus
; Complexité : O(1)
; !!! -> pas de vérification des doublons
(define (dict-add dict key val)
	(cons `(,key . ,val) dict))

; Macro pour la modification directe
(define-macro (dict-add! dico key val)
	`(set! ,dico (dict-add ,dico ,key ,val)))

; Wrapper vers dict-del-acc
; Complexité : O(N)
(define (dict-del dict key)
	(dict-del-acc '() dict key))

; Idem, mais modifie la valeur
(define-macro (dict-del! dict key)
	`(set! ,dict (dict-del-acc '() ,dict ,key)))

(define (dict-del-acc before after key)
	(cond 
		((equal? after '())
			before)
		((equal? key (car (car after)))
			(cons (car (cdr after)) before))
		(else
			(dict-del-acc (cons (car after) before) (cdr after) key))))

; Set est bien :D
(define (dict-set dict key val)
	(dict-set-acc '() dict key val))

(define (dict-set-acc before after key val)
	(cond 
		((equal? after '())
			(dict-add before key val))
		((equal? key (car (car after)))
			(append (cons (cons key val) before) (cdr after)))
		(else 
			(dict-set-acc (cons (car after) before) (cdr after) key val))))

(define-macro (dict-set! dict key val)
	`(set! ,dict (dict-set-acc '() ,dict ,key ,val)))
	
(define (dict-get-keys dict)
	(map (lambda (x) (car x)) dict))

(define (dict-get-vals dict)
	(map (lambda (x) (cdr x)) dict))

