width=150;
height=150;
length=120;
diameter=6.5;
thickness=1.5;

//hextube();

union()
{
	array();
	translate([-20,-20,-1])
	{
		difference()
		{
			cube([width+40, height+40, 4]);
			translate([20,-25,-1])
				cube([width, 40, 6]);
			translate([-25,20,-1])
				cube([40, height, 6]);
		}
	}
}

module array()
{
	union()
	{
		for(j=[0:height/(sqrt(3)*(diameter+thickness/2)/2)])
			for(i=[0:width/(sqrt(3)*(diameter+thickness/2)/2)])
				translate([i*((diameter+thickness/2)*sqrt(3)/2),(i%2)*(diameter+thickness/2)/2+
					j*sqrt(3)*(diameter+thickness/2)/2,0])
						hextube(dia = diameter, len = length, thick = thickness);
	}
}

module hextube(dia = 10, len = 50, thick = 2)
{
	difference()
	{
		cylinder(r=dia/2 + thick, h=len, $fn=6);
		translate([0,0,-5])
			cylinder(r=dia/2, h=len+10, $fn=6);
	}
}

