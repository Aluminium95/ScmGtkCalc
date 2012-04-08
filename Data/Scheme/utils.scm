;; Specific utils for ScmCalc

;; Supprime le dernier item d'une liste
(define (remove-last lst)
    (if (null? (cdr lst))
        '()
        (cons (car lst) (remove-last (cdr lst)))))
        
;; Historique des résultats
(define private-preced-list '())

;; Retourne le dernier résultat
(define (precedent)
	(car private-preced-list))

;; Retourne le n-ème résultat
(define (precedent-x x)
	(let loop ((i 1) (prec private-preced-list))
		(if (= i x)
			(car prec)
			(loop (+ i 1) (cdr prec)))))

;; Ajoute une entrée à l'histoique des résultats
(define (precedent-add x)
	(if (= (length private-preced-list) 10)
		(set! private-preced-list (cons x (remove-last private-preced-list)))
		(set! private-preced-list (cons x private-preced-list))))

(define (show-prec)
	(display private-preced-list))
