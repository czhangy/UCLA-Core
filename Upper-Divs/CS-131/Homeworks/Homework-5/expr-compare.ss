#lang racket

; Question 1 - expr-compare
(define (expr-compare x y)
    (cond
      ; Handle the case where the parameters are equal --> return the parameter
      [(equal? x y) x]
      ; Handle the boolean case --> map % to #t
      [(and (boolean? x) (boolean? y)) (if x '% '(not %))]
      ; Handle the case where one of the parameters is not a list (not a procedure call) /
      ; the case where the parameters have different lengths (different procedures)
      ; --> handle-diff immediately
      [(or
        (or (not (list? x)) (not (list? y)))
        (not (equal? (length x) (length y)))
       )
       (handle-diff x y)]
      ; Handle the general case
      [else (filter-procedure x y)]
    )
)

; Takes expressions of equal size and handles them based on the procedure call
(define (filter-procedure x y)
  (cond
    ; Handle parameters wrapped in quote --> don't enter the expression
    [(or (equal? (car x) 'quote) (equal? (car y) 'quote)) (handle-diff x y)]
    ; Handle if statements
    [(or (and (equal? (car x) 'if) (not (equal? (car y) 'if))) (and (equal? (car y) 'if) (not (equal? (car x) 'if)))) (handle-diff x y)]
    ; Handle lambda
    [(and (equal? (car x) 'lambda) (equal? (car y) 'lambda))]
    ; Handle λ and mixed lambda expressions
    [(or (and (equal? (car x) 'λ) (equal? (car y) 'λ)) (and (or (equal? (car x) 'lambda) (equal? (car x) 'λ)) (or (equal? (car y) 'lambda) (equal? (car x) 'λ))))]
    ; Handle general expressions
    [else (build-result x y)]
  )
)

; Recursive function that builds the final list
(define (build-result x y)
  (cond
    ; Base case for recursion (x is guaranteed to be equal to y in length) --> append previous results to the empty list
    [(null? x) '()]
    ; Current elements are shared by both expressions --> append common element to recursive call
    [(equal? (car x) (car y)) (cons (car x) (build-result (cdr x) (cdr y)))]
    ; Current elements are both subexpressions of equal length --> append filter-procedure to recursive call
    [(and (list? (car x)) (list? (car y)) (equal? (length (car x)) (length (car y))))
     (cons (filter-procedure (car x) (car y)) (build-result (cdr x) (cdr y)))]
    ; Other cases --> append handle-diff to recursive call
    [else (cons (handle-diff (car x) (car y)) (build-result (cdr x) (cdr y)))]
  )
)

; Handle lambda expressions
(define (handle-lambdas x y lam-type)

; Helper function for basic differences
(define (handle-diff x y)
  (list 'if '% x y)
)

; Question 2 - test-expr-compare

; Question 3 - test-expr-x and test-expr-y


; Test cases
(expr-compare '(if x y z) '(g x y z))
(display '(equal? (expr-compare 12 12) 12)) (display " is ") (equal? (expr-compare 12 12) 12)
(display '(equal? (expr-compare 12 20) '(if % 12 20))) (display " is ") (equal? (expr-compare 12 20) '(if % 12 20))
(display '(equal? (expr-compare #t #t) #t)) (display " is ") (equal? (expr-compare #t #t) #t) 
(display '(equal? (expr-compare #f #f) #f)) (display " is ") (equal? (expr-compare #f #f) #f) 
(display '(equal? (expr-compare #t #f) '%)) (display " is ") (equal? (expr-compare #t #f) '%) 
(display '(equal? (expr-compare #f #t) '(not %))) (display " is ") (equal? (expr-compare #f #t) '(not %))
(display '(equal? (expr-compare 'a '(cons a b)) '(if % a (cons a b)))) (display " is ") (equal? (expr-compare 'a '(cons a b)) '(if % a (cons a b)))
(display '(equal? (expr-compare '(cons a b) '(cons a b)) '(cons a b))) (display " is ") (equal? (expr-compare '(cons a b) '(cons a b)) '(cons a b)) 
(display '(equal? (expr-compare '(cons a lambda) '(cons a λ)) '(cons a (if % lambda λ)))) (display " is ") (equal? (expr-compare '(cons a lambda) '(cons a λ)) '(cons a (if % lambda λ))) 
(display '(equal? (expr-compare '(cons (cons a b) (cons b c))'(cons (cons a c) (cons a c)))
                 '(cons (cons a (if % b c)) (cons (if % b a) c)))) (display " is ") (equal? (expr-compare '(cons (cons a b) (cons b c))'(cons (cons a c) (cons a c)))
                 '(cons (cons a (if % b c)) (cons (if % b a) c))) 
(display '(equal? (expr-compare '(cons a b) '(list a b)) '((if % cons list) a b))) (display " is ") (equal? (expr-compare '(cons a b) '(list a b)) '((if % cons list) a b)) 
(display '(equal? (expr-compare '(list) '(list a)) '(if % (list) (list a)))) (display " is ") (equal? (expr-compare '(list) '(list a)) '(if % (list) (list a))) 
(display '(equal? (expr-compare ''(a b) ''(a c)) '(if % '(a b) '(a c)))) (display " is ") (equal? (expr-compare ''(a b) ''(a c)) '(if % '(a b) '(a c))) 
(display '(equal? (expr-compare '(quote (a b)) '(quote (a c))) '(if % '(a b) '(a c)))) (display " is ") (equal? (expr-compare '(quote (a b)) '(quote (a c))) '(if % '(a b) '(a c))) 
(display '(equal? (expr-compare '(quoth (a b)) '(quoth (a c))) '(quoth (a (if % b c))))) (display " is ") (equal? (expr-compare '(quoth (a b)) '(quoth (a c))) '(quoth (a (if % b c))))

(display '(equal? (expr-compare '(if x y z) '(if x z z)) '(if x (if % y z) z))) (display " is ") (equal? (expr-compare '(if x y z) '(if x z z)) '(if x (if % y z) z)) 
(display '(equal? (expr-compare '(if x y z) '(g x y z)) '(if % (if x y z) (g x y z)))) (display " is ") (equal? (expr-compare '(if x y z) '(g x y z)) '(if % (if x y z) (g x y z))) 
(display '(equal? (expr-compare '((lambda (a) (f a)) 1) '((lambda (a) (g a)) 2))
                 '((lambda (a) ((if % f g) a)) (if % 1 2)))) (display " is ") (equal? (expr-compare '((lambda (a) (f a)) 1) '((lambda (a) (g a)) 2))
                 '((lambda (a) ((if % f g) a)) (if % 1 2))) 
(display '(equal? (expr-compare '((lambda (a) (f a)) 1) '((λ (a) (g a)) 2))
                 '((λ (a) ((if % f g) a)) (if % 1 2)))) (display " is ") (equal? (expr-compare '((lambda (a) (f a)) 1) '((λ (a) (g a)) 2))
                 '((λ (a) ((if % f g) a)) (if % 1 2))) 
(display '(equal? (expr-compare '((lambda (a) a) c) '((lambda (b) b) d))
                 '((lambda (a!b) a!b) (if % c d)))) (display " is ") (equal? (expr-compare '((lambda (a) a) c) '((lambda (b) b) d))
                 '((lambda (a!b) a!b) (if % c d))) 
(display '(equal? (expr-compare ''((λ (a) a) c) ''((lambda (b) b) d))
                 '(if % '((λ (a) a) c) '((lambda (b) b) d)))) (display " is ") (equal? (expr-compare ''((λ (a) a) c) ''((lambda (b) b) d))
                 '(if % '((λ (a) a) c) '((lambda (b) b) d))) 
(display '(equal? (expr-compare '(+ #f ((λ (a b) (f a b)) 1 2))
                 '(+ #t ((lambda (a c) (f a c)) 1 2)))
                 '(+ (not %) ((λ (a b!c) (f a b!c)) 1 2))) ) (display " is ") (equal? (expr-compare '(+ #f ((λ (a b) (f a b)) 1 2))
                 '(+ #t ((lambda (a c) (f a c)) 1 2)))
                 '(+ (not %) ((λ (a b!c) (f a b!c)) 1 2))) 
(display '(equal? (expr-compare '((λ (a b) (f a b)) 1 2) '((λ (a b) (f b a)) 1 2))
                 '((λ (a b) (f (if % a b) (if % b a))) 1 2))) (display " is ") (equal? (expr-compare '((λ (a b) (f a b)) 1 2) '((λ (a b) (f b a)) 1 2))
                 '((λ (a b) (f (if % a b) (if % b a))) 1 2)) 
(display '(equal? (expr-compare '((λ (a b) (f a b)) 1 2) '((λ (a c) (f c a)) 1 2))
                 '((λ (a b!c) (f (if % a b!c) (if % b!c a))) 1 2))) (display " is ") (equal? (expr-compare '((λ (a b) (f a b)) 1 2) '((λ (a c) (f c a)) 1 2))
                 '((λ (a b!c) (f (if % a b!c) (if % b!c a))) 1 2)) 
(display '(equal? (expr-compare '((lambda (lambda) (+ lambda if (f lambda))) 3) '((lambda (if) (+ if if (f λ))) 3))
                 '((lambda (lambda!if) (+ lambda!if (if % if lambda!if) (f (if % lambda!if λ)))) 3))) (display " is ") (equal? (expr-compare '((lambda (lambda) (+ lambda if (f lambda))) 3) '((lambda (if) (+ if if (f λ))) 3))
                 '((lambda (lambda!if) (+ lambda!if (if % if lambda!if) (f (if % lambda!if λ)))) 3)) 
(display '(equal? (expr-compare '((lambda (a) (eq? a ((λ (a b) ((λ (a b) (a b)) b a)) a (lambda (a) a))))
                   (lambda (b a) (b a)))
                 '((λ (a) (eqv? a ((lambda (b a) ((lambda (a b) (a b)) b a)) a (λ (b) a))))
                   (lambda (a b) (a b)))) '((λ (a)
                 ((if % eq? eqv?) a
                 ((λ (a!b b!a) ((λ (a b) (a b)) (if % b!a a!b) (if % a!b b!a)))
                 a (λ (a!b) (if % a!b a)))))
                 (lambda (b!a a!b) (b!a a!b)))) ) (display " is ") (equal? (expr-compare '((lambda (a) (eq? a ((λ (a b) ((λ (a b) (a b)) b a)) a (lambda (a) a))))
                   (lambda (b a) (b a)))
                 '((λ (a) (eqv? a ((lambda (b a) ((lambda (a b) (a b)) b a)) a (λ (b) a))))
                   (lambda (a b) (a b)))) '((λ (a)
                 ((if % eq? eqv?) a
                 ((λ (a!b b!a) ((λ (a b) (a b)) (if % b!a a!b) (if % a!b b!a)))
                 a (λ (a!b) (if % a!b a)))))
                 (lambda (b!a a!b) (b!a a!b)))) 