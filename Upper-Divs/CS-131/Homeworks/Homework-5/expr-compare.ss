#lang racket
(provide expr-compare)

; Question 1 - expr-compare
(define (expr-compare x y)
    (cond
      ; Handle the case where the parameters are equal --> return the parameter
      [(equal? x y)
       x]
      ; Handle the boolean case --> map % to #t
      [(and (boolean? x) (boolean? y))
       (if x '% '(not %))]
      ; One of the expressions is not a list
      [(or (not (list? x)) (not (list? y)))
       (handle-diff x y)]
      ; Both expressions are lists
      [else
       (let ([x-head (car x)]
             [y-head (car y)]
             [x-tail (cdr x)]
             [y-tail (cdr y)])
         #|
         Procedure calls are different +
         One of the expressions is quoted +
         One of the expressions is an if statement +
         One of the expressions is a lambda expression
         --> handle-diff immediately
         |#
         (cond
          [(or
            (not (equal? (length x) (length y)))
            (or (quote? x-head) (quote? y-head))
            (xor (if? x-head) (if? y-head))
            (xor (lambda? x-head) (lambda? y-head))
            )
           (handle-diff x y)]
          ; Handle lambda expressions
          [(and (lambda? x-head) (lambda? y-head))
           (if (equal? (length (car x-tail)) (length (car y-tail)))
               ; Arguments match --> check for correct type of lambda
               (if (and (equal? x-head 'lambda) (equal? y-head 'lambda))
                   (handle-lambdas x-tail y-tail 'lambda '() '())
                   (handle-lambdas x-tail y-tail 'λ '() '()))
               ; Unequal length of arguments
               (handle-diff x y))]
          ; Handle the general case
          [else
           (handle-exp x y)]
          )
         )
       ]
      )
  )

; Recursive function that builds an expression
(define (handle-exp x y)
  ; Base case
  (if (null? x) '()
      (let ([x-head (car x)]
            [x-tail (cdr x)]
            [y-head (car y)]
            [y-tail (cdr y)]
            [recursive-call (handle-exp (cdr x) (cdr y))])
        (cond
          ; Current elements are shared by both expressions --> append common element to recursive call
          [(equal? x-head y-head)
           (cons x-head recursive-call)]
          ; Current elements are booleans
          [(and (boolean? x-head) (boolean? y-head))
           (cons (if x-head '% '(not %)) recursive-call)]
          ; Current elements are both subexpressions of equal length --> append expr-compare to recursive call
          [(and (list? x-head) (list? y-head) (equal? (length x-head) (length y-head)))
           (cons (expr-compare x-head y-head) recursive-call)]
          ; Other cases --> append handle-diff to recursive call
          [else
           (cons (handle-diff x-head y-head) recursive-call)]
        )
      )
  )
)

; Handle lambda expressions
(define (handle-lambdas x y lam-type x-set y-set)
  (let ([x-params (car x)]
        [x-body (car (cdr x))]
        [y-params (car y)]
        [y-body (car (cdr y))])
    ; Begin list with 'lambda or 'λ, followed by params, followed by body
    (list lam-type (handle-lambda-params x-params y-params)
          (handle-lambda-body x-body y-body (cons (hash-params x-params y-params #t) x-set)
                              (cons (hash-params x-params y-params #f) y-set)))
  )
)

; Handle lambda parameters
(define (handle-lambda-params x y)
  ; Base case
  (if (empty? x) '()
      (let ([x-head (car x)]
            [y-head (car y)]
            [recursive-call (handle-lambda-params (cdr x) (cdr y))])
        (if (equal? x-head y-head)
          ; Get matching parameters
          (cons x-head recursive-call)
          ; Unify distinct parameters
          (cons (unify-params x-head y-head) recursive-call)
        )
      )
  )
)

; Handle lambda body --> similar to expr-compare, but account for mappings
(define (handle-lambda-body x y x-set y-set)
  ; Get aliases for x and y
  (let ([x-alias (if (discover-alias x x-set) (discover-alias x x-set) x)]
        [y-alias (if (discover-alias y y-set) (discover-alias y y-set) y)])
    (cond
      ; Bodies are equal/unified
      [(equal? x-alias y-alias)
       x-alias]
      ; Bodies are boolean
      [(and (boolean? x-alias) (boolean? y-alias))
       (if x '% '(not %))]
      ; One of the bodies is not a procedure call
      [(or (not (list? x-alias)) (not (list? y-alias)))
       (handle-diff (if (list? x-alias) (apply-alias x-alias x-set) x-alias)
                    (if (list? y-alias) (apply-alias y-alias y-set) y-alias))]
      ; The bodies are lists
      [else
       (let ([x-head (car x)]
             [x-tail (cdr x)]
             [y-head (car y)]
             [y-tail (cdr y)])
         (cond
           ; One of the bodies is quoted
           [(or (quote? x-head) (quote? x-head))
            (handle-diff x y)]
           ; Procedure calls are different lengths +
           ; One of the bodies is an if-statement +
           [(or
             (not (equal? (length x) (length y)))
             (xor (if? x-head) (if? y-head)))
            (handle-diff (apply-alias x x-set) (apply-alias y y-set))]
           ; Handle nested-lambdas
           [(and (equal? x-head 'lambda) (equal? y-head 'lambda))
            (handle-lambdas x-tail y-tail 'lambda x-set y-set)]
           ; Handle nested-λs
           [(and (lambda? x-head) (lambda? y-head))
            (handle-lambdas x-tail y-tail 'λ x-set y-set)]
           ; Both subexpressions are lists of equal length
           [else
            (handle-lambda-subexp x y x-set y-set)]
           )
         )
       ]
      )
    )
  )

; Handle any subexpressions within the body of a lambda expression
(define (handle-lambda-subexp x y x-set y-set)
  (if (empty? x) '()
      ; Get aliases for x and y
      (let ([x-alias (if (discover-alias (car x) x-set) (discover-alias (car x) x-set) (car x))]
            [y-alias (if (discover-alias (car y) y-set) (discover-alias (car y) y-set) (car y))]
            [recursive-call (handle-lambda-subexp (cdr x) (cdr y) x-set y-set)])
        (cond
          ; Current elements are equal/unified
          [(equal? x-alias y-alias)
           (cons x-alias recursive-call)]
          ; Current elements are boolean
          [(and (boolean? x-alias) (boolean? y-alias))
           (cons (if x-alias '% '(not %)) recursive-call)]
          ; Check if current elements are both lists
          [(and (list? x-alias) (list? y-alias))
           (if (equal? (length x-alias) (length y-alias))
               ; Even lists --> treat list as another lambda body, cons
               (cons (handle-lambda-body x-alias y-alias x-set y-set) recursive-call)
               ; Uneven lists --> alias params, handle-diff, cons
               (cons (handle-diff (apply-alias x-alias x-set) (apply-alias y-alias y-set)) recursive-call))]
          ; One of the current elements is a list
          [(or (list? x-alias) (list? y-alias))
           (handle-diff (if (list? x) (apply-alias x x-set) x-alias) (if (list? y) (apply-alias y y-set) y-alias))]
          ; General case
          [else
           (cons (handle-diff x-alias y-alias) recursive-call)]
          )
        )
  )
)

; Build hash map for parameters for x (order matters for x!y)
(define (hash-params x y is-x)
  ; Base case
  (if (empty? x) (hash)
      (let ([x-head (car x)]
            [x-tail (cdr x)]
            [y-head (car y)]
            [y-tail (cdr y)])
        (if (equal? x-head y-head)
          ; Map to self if params correspond
           (hash-set (hash-params x-tail y-tail is-x) x-head x-head)
          ; Map to formatted param for mismatching params 
           (if is-x
               (hash-set (hash-params x-tail y-tail is-x) x-head (unify-params x-head y-head))
               (hash-set (hash-params x-tail y-tail is-x) y-head (unify-params x-head y-head)))
          )
        )
  )
)

; Find out if an alias exists in a hash map
(define (discover-alias x map-list)
  ; Base case, return #f to represent x not in hash map
  (if (empty? map-list) #f
      (let ([head (car map-list)]
            [tail (cdr map-list)])
        (if (hash-ref (car map-list) x #f)
          ; Mapping found in current hash map
           (hash-ref (car map-list) x)
          ; Search next hash map
           (discover-alias x (cdr map-list))
        )
      )
  )
)

; Replace params with their alias
(define (apply-alias x x-set)
  ; Base case
  (if (empty? x) '()
      (let ([head (car x)]
            [tail (cdr x)])
        ; Append alias to recursive call
        (cons (if (discover-alias head x-set)
                  (discover-alias head x-set)
                  head)
              (apply-alias tail x-set))
      )
  )
)

; Helper function for basic differences
(define (handle-diff x y)
  (list 'if '% x y)
)

; Helper function to generate x!y format
(define (unify-params x y)
  (string->symbol (string-append (symbol->string x) "!" (symbol->string y)))
)

; Predicate to detect lambda
(define (lambda? x)
  (if (or (equal? x 'lambda) (equal? x 'λ)) #t #f)
)

; Predicate to detect if
(define (if? x)
  (if (equal? x 'if) #t #f)
)

; Predicate to detect quote
(define (quote? x)
  (if (equal? x 'quote) #t #f)
)

; Question 2 - test-expr-compare
(define (test-expr-compare x y) 
  (and (equal? (eval x)
               (eval `(let ((% #t)), (expr-compare x y))))
       (equal? (eval y)
               (eval `(let ((% #f)), (expr-compare x y))))))

; Question 3 - test-expr-x and test-expr-y
(define test-expr-x `(50 (quote a) ((lambda (c d) ((if c #t #f) (cons d '()))))))
(define test-expr-y `(60 (quote b) ((lambda (e f) ((if e #f #t) (equal? f '()))))))

; Test cases
(and
 (equal? (expr-compare 12 12) 12)
 (equal? (expr-compare 12 20) '(if % 12 20))
 (equal? (expr-compare #t #t) #t) 
 (equal? (expr-compare #f #f) #f) 
 (equal? (expr-compare #t #f) '%) 
 (equal? (expr-compare #f #t) '(not %))
 (equal? (expr-compare 'a '(cons a b)) '(if % a (cons a b)))
 (equal? (expr-compare '(cons a b) '(cons a b)) '(cons a b)) 
 (equal? (expr-compare '(cons a lambda) '(cons a λ)) '(cons a (if % lambda λ))) 
 (equal? (expr-compare '(cons (cons a b) (cons b c))'(cons (cons a c) (cons a c)))
         '(cons (cons a (if % b c)) (cons (if % b a) c))) 
 (equal? (expr-compare '(cons a b) '(list a b)) '((if % cons list) a b)) 
 (equal? (expr-compare '(list) '(list a)) '(if % (list) (list a))) 
 (equal? (expr-compare ''(a b) ''(a c)) '(if % '(a b) '(a c))) 
 (equal? (expr-compare '(quote (a b)) '(quote (a c))) '(if % '(a b) '(a c))) 
 (equal? (expr-compare '(quoth (a b)) '(quoth (a c))) '(quoth (a (if % b c))))
 (equal? (expr-compare '(if x y z) '(if x z z)) '(if x (if % y z) z)) 
 (equal? (expr-compare '(if x y z) '(g x y z)) '(if % (if x y z) (g x y z)))
 (equal? (expr-compare '((lambda (a) (f a)) 1) '((lambda (a) (g a)) 2))
         '((lambda (a) ((if % f g) a)) (if % 1 2))) 
 (equal? (expr-compare '((lambda (a) (f a)) 1) '((λ (a) (g a)) 2))
         '((λ (a) ((if % f g) a)) (if % 1 2))) 
 (equal? (expr-compare '((lambda (a) a) c) '((lambda (b) b) d))
         '((lambda (a!b) a!b) (if % c d))) 
 (equal? (expr-compare ''((λ (a) a) c) ''((lambda (b) b) d))
         '(if % '((λ (a) a) c) '((lambda (b) b) d)))
 (equal? (expr-compare '(+ #f ((λ (a b) (f a b)) 1 2))
                       '(+ #t ((lambda (a c) (f a c)) 1 2)))
         '(+ (not %) ((λ (a b!c) (f a b!c)) 1 2))) 
 (equal? (expr-compare '((λ (a b) (f a b)) 1 2) '((λ (a b) (f b a)) 1 2))
         '((λ (a b) (f (if % a b) (if % b a))) 1 2)) 
 (equal? (expr-compare '((λ (a b) (f a b)) 1 2) '((λ (a c) (f c a)) 1 2))
         '((λ (a b!c) (f (if % a b!c) (if % b!c a))) 1 2)) 
 (equal? (expr-compare '((lambda (lambda) (+ lambda if (f lambda))) 3) '((lambda (if) (+ if if (f λ))) 3))
         '((lambda (lambda!if) (+ lambda!if (if % if lambda!if) (f (if % lambda!if λ)))) 3)) 
 (equal? (expr-compare '((lambda (a) (eq? a ((λ (a b) ((λ (a b) (a b)) b a)) a (lambda (a) a))))
                         (lambda (b a) (b a)))
                       '((λ (a) (eqv? a ((lambda (b a) ((lambda (a b) (a b)) b a)) a (λ (b) a))))
                         (lambda (a b) (a b)))) '((λ (a)
                                                    ((if % eq? eqv?) a
                                                                     ((λ (a!b b!a) ((λ (a b) (a b)) (if % b!a a!b) (if % a!b b!a)))
                                                                      a (λ (a!b) (if % a!b a)))))
                                                  (lambda (b!a a!b) (b!a a!b))))


 (equal? (expr-compare '(cons a lambda) '(cons a λ)) '(cons a (if % lambda λ)))
 (equal? (expr-compare '(lambda (a) a) '(lambda (b) b)) '(lambda (a!b) a!b))
 (equal? (expr-compare '(lambda (a) b) '(cons (c) b)) '(if % (lambda (a) b) (cons (c) b)))
 (equal? (expr-compare '((λ (if) (+ if 1)) 3) '((lambda (fi) (+ fi 1)) 3)) '((λ (if!fi) (+ if!fi 1)) 3))
 (equal? (expr-compare '(lambda (lambda) lambda) '(λ (λ) λ)) '(λ (lambda!λ) lambda!λ))
 (equal? (expr-compare ''lambda '(quote λ)) '(if % 'lambda 'λ))
 (equal? (expr-compare '(lambda (a b) a) '(λ (b) b)) '(if % (lambda (a b) a) (λ (b) b)))
 (equal? (expr-compare '(λ (a b) (lambda (b) b)) '(lambda (b) (λ (b) b))) '(if % (λ (a b) (lambda (b) b)) (lambda (b) (λ (b) b))))
 (equal? (expr-compare '(λ (let) (let ((x 1)) x)) '(lambda (let) (let ((y 1)) y))) '(λ (let) (let (((if % x y) 1)) (if % x y))))
 (equal? (expr-compare '(λ (x) ((λ (x) x) x))
                       '(λ (y) ((λ (x) y) x))) '(λ (x!y) ((λ (x) (if % x x!y)) (if % x!y x))))
 (equal? (expr-compare '(((λ (g)
                            ((λ (x) (g (λ () (x x))))     ; This is the way we define a recursive function
                             (λ (x) (g (λ () (x x))))))   ; when we don't have 'letrec'
                          (λ (r)                               ; Here (r) will be the function itself
                            (λ (n) (if (= n 0)
                                       1
                                       (* n ((r) (- n 1))))))) ; Therefore this thing calculates factorial of n
                         10)
                       '(((λ (x)
                            ((λ (n) (x (λ () (n n))))
                             (λ (r) (x (λ () (r r))))))
                          (λ (g)
                            (λ (x) (if (= x 0)
                                       1
                                       (* x ((g) (- x 1)))))))
                         9)) '(((λ (g!x)
                                  ((λ (x!n) (g!x (λ () (x!n x!n))))
                                   (λ (x!r) (g!x (λ () (x!r x!r))))))
                                (λ (r!g)
                                  (λ (n!x) (if (= n!x 0)
                                               1
                                               (* n!x ((r!g) (- n!x 1)))))))
                               (if % 10 9)))
)