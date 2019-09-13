difference()
{
translate([-6,-7.5,-8])
cube([20,15,16]);

translate([0,0,0])
cylinder(r=3,h=20,center=true,$fn=30);

translate([8,0,0])
rotate([90,0,0])
cylinder(r=4,h=20,center=true,$fn=30);

translate([0,-1,-15])
cube([30,2,30]);
}



