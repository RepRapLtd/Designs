difference()
{
	linear_extrude(file = "bog-lever.dxf", layer = "0",
  		height = 15, center = true, convexity = 10, twist = 0);
	translate([47,0,15])
		cube([70,8,30], center=true);
	translate([74,0,15])
		cube([20,20,30], center=true);
}
	