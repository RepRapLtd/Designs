
difference()
{
union()
{
cylinder(r=4.5,h=20, center=true, $fn=50);
translate([0,0,-10])
cylinder(r=6,h=2, center=true, $fn=50);
}
translate([0,0,1])
cylinder(r=3,h=20, center=true, $fn=50);

translate([1.4,0,0])
cylinder(r=0.7,h=40, center=true, $fn=50);
translate([-1.4,0,0])
cylinder(r=0.7,h=40, center=true, $fn=50);


}