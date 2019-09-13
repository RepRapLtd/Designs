
module clamp()
{
	difference()
	{
		union()
		{
			translate([0,10,3.5])
				cube([20,40,7],center=true);
			
			translate([0,25,8.5])
				cube([20,10,10],center=true);
			
			translate([0,10,3.5])
				cube([20,40,7],center=true);
			
			translate([0,0,13])
				cylinder(r=6.75, h= 25,center=true,$fn=30);
		}

		translate([9,0,0])
			cube([20,2,57],center=true);
		
		translate([0,26,0])
			cube([8,20,57],center=true);
		
		translate([0,0,28])
			cylinder(r=3.25, h= 20,center=true,$fn=20);
		
		//cylinder(r=1, h= 70,center=true,$fn=10);
		
		translate([0,25,8.5])
			rotate([0,90,0])
				cylinder(r=1.6, h= 40,center=true,$fn=20);
	}
}


module lever()
{
	difference()
	{
		union()
		{
			translate([0,5,3.5])
				cube([20,50,7],center=true);
			translate([0,25,12])
				cube([20,10,17],center=true);
		
		}
		
		translate([13,25,0])
			cube([20,20,50],center=true);
		translate([-13,25,0])
			cube([20,20,50],center=true);
		
		translate([0,5,0])
			cube([2,10,57],center=true);
		
		translate([0,8,0])
			cube([9,7,57],center=true);
		
		cylinder(r=1, h= 70,center=true,$fn=10);
		
		translate([0,25,16])
			rotate([0,90,0])
				cylinder(r=1.6, h= 40,center=true,$fn=20);
		
		translate([0,0,-2])
			rotate([45,0,0])
				cube([9,6,6],center=true);
	}
}



//translate([0,0,-37])
	lever();

//clamp();