/*
1)  Square (n = 4) is the only regular polygon with integer coordinates 

2)  Pick's theorem:  A = i + b/2 - 1
    A: area of the polygon
    i: number of interior points
    b: number of points on the border

3) Conic Rotations
    Given elipse: Ax^2 + Bxy + Cy^2 + Dx + Ey + F = 0
    Convert it to: Ax^2 + Bxy + Cy^2 + Dx + Ey = 1 (this formula suits better for elipse, before doing this verify F = 0)
    Final conversion: A(x + D/2A)^2 + C(y + E/2C)^2 = 1 + D^2/4A + E^2/4C
        B != 0 (Rotate):
            theta = atan2(b, c-a)/2.0; 
            A' = (a + c + b/sin(2.0*theta))/2.0; // A
            C' = (a + c - b/sin(2.0*theta))/2.0; // C
            D' = d*sin(theta) + e*cos(theta); // D
            E' = d*cos(theta) - e*sin(theta); // E
        Remember to rotate again after!
*/


// determine if point is in a possibly non-convex polygon (by William
// Randolph Franklin); returns 1 for strictly interior points, 0 for
// strictly exterior points, and 0 or 1 for the remaining points.
// Note that it is possible to convert this into an *exact* test using
// integer arithmetic by taking care of the division appropriately
// (making sure to deal with signs properly) and then by writing exact
// tests for checking point on polygon boundary
bool PointInPolygon(const vector<PT> &p, PT q) {
    bool c = 0;
    for (int i = 0; i < p.size(); i++){
        int j = (i+1)%p.size();
        if ((p[i].y <= q.y && q.y < p[j].y || 
            p[j].y <= q.y && q.y < p[i].y) &&
            q.x < p[i].x + (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y))
            c = !c;
    }
    return c;
}