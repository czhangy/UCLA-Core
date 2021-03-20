% ---------------------------------------------------------------------------------------------
% transpose/2: Transposes a matrix, allowing generalization of row check code to column checks
% ---------------------------------------------------------------------------------------------
transpose([], []).
transpose([F|Fs], Ts) :-
    transpose(F, [F|Fs], Ts).
transpose([], _, []).
transpose([_|Rs], Ms, [Ts|Tss]) :-
        lists_firsts_rests(Ms, Ts, Ms1),
        transpose(Rs, Ms1, Tss).
lists_firsts_rests([], [], []).
lists_firsts_rests([[F|Os]|Rest], [F|Fs], [Os|Oss]) :-
        lists_firsts_rests(Rest, Fs, Oss).

% ---------------------------------------------------------------------------------------------
% valid_row/2: Checks if a given row is structurally valid by KenKen conditions
% ---------------------------------------------------------------------------------------------
valid_row(Len, Row) :-
    % Check for correct length
    length(Row, Len),
    % Check that there are no invalid values
    fd_domain(Row, 1, Len),
    % Check that all values are unique
    fd_all_different(Row).

% ---------------------------------------------------------------------------------------------
% valid_structure/2: Checks if a given matrix is structurally valid by KenKen conditions
% ---------------------------------------------------------------------------------------------
valid_structure(_, []).
valid_structure(Dim, [Head|Tail]) :-
    % Check the current row
    valid_row(Dim, Head),
    % Check the rest of the rows
    valid_structure(Dim, Tail).

% ---------------------------------------------------------------------------------------------
% valid_dimensions/2: Checks if a given matrix is dimensionally valid by KenKen conditions
% ---------------------------------------------------------------------------------------------
valid_dimensions(Dim, Matrix) :-
    length(Matrix, Dim),
    % Check the rows
    valid_structure(Dim, Matrix),
    transpose(Matrix, TMatrix),
    % Check the columns
    valid_structure(Dim, TMatrix).

% ---------------------------------------------------------------------------------------------
% get_val/3: Access the value at a given square
% ---------------------------------------------------------------------------------------------
get_val([Row|Col], Matrix, Val) :-
    % Check row
    nth(Row, Matrix, Temp),
    % Check column
    nth(Col, Temp, Val).

% ---------------------------------------------------------------------------------------------
% apply_x_constraint/3: Enforces a sum or product constraint
% ---------------------------------------------------------------------------------------------
apply_sum_constraint([], _, Sum) :- Sum = 0.
apply_sum_constraint([Head|Tail], Matrix, Sum) :-
    % Get value at the current square
    get_val(Head, Matrix, Val),
    apply_sum_constraint(Tail, Matrix, RestSum),
    % Add the current value to the rest of the values
    Sum = Val + RestSum.

apply_prod_constraint([], _, Prod) :- Prod = 1.
apply_prod_constraint([Head|Tail], Matrix, Prod) :-
    % Get value at the current square
    get_val(Head, Matrix, Val),
    apply_prod_constraint(Tail, Matrix, RestProd),
    % Multiply the current value to the rest of the values
    Prod = Val * RestProd.

% ---------------------------------------------------------------------------------------------
% handle_constraint/2: Redirect to correct constraint check
% ---------------------------------------------------------------------------------------------
% Handle sum constraints
handle_constraint(+(S, L), Matrix) :- 
    % Get sum of cage
    apply_sum_constraint(L, Matrix, TestSum),
    % Compare
    TestSum #= S.

% Handle product constraints
handle_constraint(*(P, L), Matrix) :- 
    % Get product of cage
    apply_prod_constraint(L, Matrix, TestProd),
    % Compare
    TestProd #= P.

% Handle difference constraints
handle_constraint(-(D, J, K), Matrix) :- 
    % Get values at the given squares
    get_val(J, Matrix, ValJ),
    get_val(K, Matrix, ValK),
    % Compare both possibilities
    (D #= ValJ - ValK; D #= ValK - ValJ).

% Handle quotient constraints
handle_constraint(/(Q, J, K), Matrix) :- 
    % Get values at the given squares
    get_val(J, Matrix, ValJ),
    get_val(K, Matrix, ValK),
    % Compare both possibilities
    (Q #= ValJ / ValK; Q #= ValK / ValJ).

% ---------------------------------------------------------------------------------------------
% check_constraints/2: Proves all constraints
% ---------------------------------------------------------------------------------------------
check_constraints([], _).
check_constraints([Head|Tail], Matrix) :-
    % Handle current constraint
    handle_constraint(Head, Matrix),
    % Handle rest of constraints
    check_constraints(Tail, Matrix).

% ---------------------------------------------------------------------------------------------
% label/1: Label each row
% ---------------------------------------------------------------------------------------------
label([]).
label([Head|Tail]) :-
    % Label current row
    fd_labeling(Head),
    % Label rest of rows
    label(Tail).

% ---------------------------------------------------------------------------------------------
% kenken/3: Use the finite domain solver to implement a KenKen solver
% ---------------------------------------------------------------------------------------------
kenken(N, C, T) :-
    % T is NxN, all values are between 1, 2, ..., N, every row/col is a permuatation of [1, 2, ..., N]
    valid_dimensions(N, T),
    % Meet the constraints given by C
    check_constraints(C, T),
    label(T).

% ---------------------------------------------------------------------------------------------
% plain_valid_row/2: Checks if a given row is structurally valid by KenKen conditions
% ---------------------------------------------------------------------------------------------
plain_valid_row(Len, Row) :-
    % Make a list of values from 1, ..., Len
    findall(X, between(1, Len, X), L),
    % Check if this list is a permutation of Row
    permutation(L, Row).

% ---------------------------------------------------------------------------------------------
% plain_valid_structure/2: Checks if a given matrix is structurally valid by KenKen conditions
% ---------------------------------------------------------------------------------------------
plain_valid_structure(_, []).
plain_valid_structure(Dim, [Head|Tail]) :-
    % Check the current row
    plain_valid_row(Dim, Head),
    % Check the rest of the rows
    plain_valid_structure(Dim, Tail).

% ---------------------------------------------------------------------------------------------
% plain_valid_dimensions/2: Checks if a given matrix is dimensionally valid by KenKen conditions
% ---------------------------------------------------------------------------------------------
plain_valid_dimensions(Dim, Matrix) :-
    length(Matrix, Dim),
    % Check the rows
    plain_valid_structure(Dim, Matrix),
    transpose(Matrix, TMatrix),
    % Check the columns
    plain_valid_structure(Dim, TMatrix).

% ---------------------------------------------------------------------------------------------
% handle_constraint/2: Redirect to correct constraint check
% ---------------------------------------------------------------------------------------------
plain_handle_constraint(+(S, L), Matrix) :- 
    apply_sum_constraint(L, Matrix, TestSum),
    TestSum =:= S.

plain_handle_constraint(*(P, L), Matrix) :- 
    apply_prod_constraint(L, Matrix, TestProd),
    TestProd =:= P.

plain_handle_constraint(-(D, J, K), Matrix) :- 
    get_val(J, Matrix, ValJ),
    get_val(K, Matrix, ValK),
    (D =:= ValJ - ValK; D =:= ValK - ValJ).

plain_handle_constraint(/(Q, J, K), Matrix) :- 
    get_val(J, Matrix, ValJ),
    get_val(K, Matrix, ValK),
    (Q =:= ValJ / ValK; Q =:= ValK / ValJ).

% ---------------------------------------------------------------------------------------------
% plain_check_constraints/2: Proves all constraints
% ---------------------------------------------------------------------------------------------
plain_check_constraints([], _).
plain_check_constraints([Head|Tail], Matrix) :-
    plain_handle_constraint(Head, Matrix),
    plain_check_constraints(Tail, Matrix).

% ---------------------------------------------------------------------------------------------
% plain_kenken/3: Use standard Prolog primitives to implement a KenKen solver
% ---------------------------------------------------------------------------------------------
plain_kenken(N, C, T) :- 
    plain_valid_dimensions(N, T),
    plain_check_constraints(C, T).

% ---------------------------------------------------------------------------------------------
% statistics/0: Measure kenken/3 performance vs. plain_kenken/3 performance
% ---------------------------------------------------------------------------------------------
% ~0ms - kenken 4x4
time_test :-
    statistics(real_time, [KenkenInit|_]),
    kenken(
        4,
        [
            +(7, [[1|1], [1|2], [1|3]]),
            +(8, [[1|4], [2|3], [2|4]]),
            *(288, [[2|1], [2|2], [3|1], [3|2], [4|1]]),
            /(2, [3|3], [3|4]),
            *(6, [[4|2], [4|3], [4|4]])
        ], 
        T
    ), write(T), nl,
    statistics(real_time, [KenKenFinal|_]),
    KenkenRuntime is KenKenFinal - KenkenInit,
    write(KenkenRuntime).

% ~120ms - plain_kenken 4x4
plain_time_test :-
    statistics(real_time, [PlainKenkenInit|_]),
    plain_kenken(
        4,
        [
            +(7, [[1|1], [1|2], [1|3]]),
            +(8, [[1|4], [2|3], [2|4]]),
            *(288, [[2|1], [2|2], [3|1], [3|2], [4|1]]),
            /(2, [3|3], [3|4]),
            *(6, [[4|2], [4|3], [4|4]])
        ], 
        T
    ), write(T), nl,
    statistics(real_time, [PlainKenKenFinal|_]),
    PlainKenkenRuntime is PlainKenKenFinal - PlainKenkenInit,
    write(PlainKenkenRuntime).

% ---------------------------------------------------------------------------------------------
% noop_kenken/4
% ---------------------------------------------------------------------------------------------
noop_kenken(Dimension, Cages, Operators, T) :- true.
/*
    This API takes in the same N and T parameters as kenken/3 and plain_kenken/3 (renamed to
    Dimension and T). It adds an additional Operators parameter. It modifies the C parameter
    (renamed to Cages), by passing it a list of lists rather than a list of compound terms.
    kenken_3 and plain_kenken/3 essentially created valid matrices according to general KenKen 
    principles, then proceeded to check if those matrix distributions satisfied the constraints 
    set by the combination of cages and operators. In noop_kenken, the predicate will instead 
    start by generating all possible operator distributions (each cage must be 1 of 4 operators),
    unifying the list of constraint + operators into Operators, and then proceeding with normal
    kenken/3 or plain_kenken/3 execution. Upon success, the Operators term will contain a list
    of constraints, exactly like the ones passed as C into kenken/3 and plain_kenken/3. 
*/

noop_kenken_testcase :-
    noop_kenken(
        4,
        [
            [6, [[1|1], [1|2], [2|1]]],
            [96, [[1|3], [1|4], [2|2], [2|3], [2|4]]],
            [1, [[3|1], [3|2]]],
            [1, [[4|1], [4|2]]],
            [8, [[3|3], [4|3], [4|4]]],
            [2, [[3|4]]]
        ],
        Ops,
        T
    ), write(Ops), write(T), nl, fail.

% ---------------------------------------------------------------------------------------------
% Test Cases
% ---------------------------------------------------------------------------------------------
% Multiplication only 3x3
test0 :-
    plain_kenken(
        3,
        [
            *(3, [[1|1], [1|2]]),
            *(6, [[2|1], [2|2], [3|1]]),
            *(2, [[3|2], [3|3]]),
            *(6, [[1|3], [2|3]])
        ], 
        T
    ), write(T), nl, fail.
    
% Fixed-domain 6x6
test1 :-
    fd_set_vector_max(255),
    kenken(
        6,
        [
            +(11, [[1|1], [2|1]]),
            /(2, [1|2], [1|3]),
            *(20, [[1|4], [2|4]]),
            *(6, [[1|5], [1|6], [2|6], [3|6]]),
            -(3, [2|2], [2|3]),
            /(3, [2|5], [3|5]),
            *(240, [[3|1], [3|2], [4|1], [4|2]]),
            *(6, [[3|3], [3|4]]),
            *(6, [[4|3], [5|3]]),
            +(7, [[4|4], [5|4], [5|5]]),
            *(30, [[4|5], [4|6]]),
            *(6, [[5|1], [5|2]]),
            +(9, [[5|6], [6|6]]),
            +(8, [[6|1], [6|2], [6|3]]),
            /(2, [6|4], [6|5])
        ],
        T
    ), write(T), nl, fail.

% kenken 4x4
test2 :-
    kenken(
        4,
        [
            +(7, [[1|1], [1|2], [1|3]]),
            +(8, [[1|4], [2|3], [2|4]]),
            *(288, [[2|1], [2|2], [3|1], [3|2], [4|1]]),
            /(2, [3|3], [3|4]),
            *(6, [[4|2], [4|3], [4|4]])
        ], 
        T
    ), write(T), nl, fail.

% plain_kenken 4x4
test3 :-
    plain_kenken(
        5,
        [
            /(2, [1|1], [2|1]),
            *(10, [[1|2], [1|3]]),
            -(2, [1|4], [1|5]),
            +(9, [[2|2], [3|1], [3|2], [3|3]]),
            +(12, [[2|3], [2|4], [2|5]]),
            +(7, [[3|4], [3|5]]),
            +(8, [[4|1], [5|1], [5|2]]),
            -(2, [4|2], [4|3]),
            +(3, [[5|3]]),
            +(7, [[4|4], [5|4], [5|5]]),
            +(4, [[4|5]])
        ], 
        T
    ), write(T), nl, fail.

% plain_kenken 6x6
test4 :-
    plain_kenken(
        6,
        [
            +(11, [[1|1], [2|1]]),
            /(2, [1|2], [1|3]),
            *(20, [[1|4], [2|4]]),
            *(6, [[1|5], [1|6], [2|6], [3|6]]),
            -(3, [2|2], [2|3]),
            /(3, [2|5], [3|5]),
            *(240, [[3|1], [3|2], [4|1], [4|2]]),
            *(6, [[3|3], [3|4]]),
            *(6, [[4|3], [5|3]]),
            +(7, [[4|4], [5|4], [5|5]]),
            *(30, [[4|5], [4|6]]),
            *(6, [[5|1], [5|2]]),
            +(9, [[5|6], [6|6]]),
            +(8, [[6|1], [6|2], [6|3]]),
            /(2, [6|4], [6|5])
        ],
        T
    ), write(T), nl, fail.