/*
1)  Square (n = 4) is the only regular polygon with integer coordinates 

2)  Pick's theorem:  A = i + b/2 - 1
    A: area of the polygon
    i: number of interior points
    b: number of points on the border

3) Conic Rotations
    Given elipse: Ax² + Bxy + Cy² + Dx + Ey + F = 0
    Convert it to: Ax² + Bxy + Cy² + Dx + Ey = 1 (this formula suits better for elipse, before doing this verify F = 0)
    Final conversion: A(x + D/2A)² + C(y + E/2C)² = 1 + D²/4A + E²/4C
        B != 0 (Rotate):
            theta = atan2(b, c-a)/2.0; 
            A' = (a + c + b/sin(2.0*theta))/2.0; // A
            C' = (a + c - b/sin(2.0*theta))/2.0; // C
            D' = d*sin(theta) + e*cos(theta); // D
            E' = d*cos(theta) - e*sin(theta); // E
        Remember to rotate again after!
*/