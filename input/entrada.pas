program sistema;

var
    x, y : integer;
    media : real;

begin
    x := 10;
    y := 20;

    if x < y then
        media := (x + y) / 2;

    while x < y do
        x := x + 1;
end.