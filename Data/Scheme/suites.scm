(define (fact n)
    (let loop ((fact 1)
               (n n))
      (cond ((= n 0) fact)
            (else (loop (* n fact) (- n 1))))))
            
(define (fib n)
  (let fib ((a 0)
            (b 1)
            (n n))
    (if (< n 1)
        a
        (fib b (+ a b) (- n 1)))))
