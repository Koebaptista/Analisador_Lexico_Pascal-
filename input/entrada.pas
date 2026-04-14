program Teste;
var
x, y : integer;
z : real;
begin
x := 10;
y := 20;
z := 2.5;
x := x + y * 2;

x := 20.;      { erro número mal formado }
y := 10 @ 2;   { erro caractere inválido }

{ comentário não fechado
end.