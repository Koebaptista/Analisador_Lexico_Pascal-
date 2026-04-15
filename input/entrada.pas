program TesteCompleto;
var
a, b, c : integer;
x : real;

begin
a := 10;
b := 20;
c := a + b * 2;

x := 3.14;
x := 20.;        { erro número mal formado }

y := 10 @ 2;     { erro caractere inválido }

{ comentário não fechado
end.