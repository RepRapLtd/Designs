module box(x = 10, y = 20, z = 30, center = false)
{
	scale([x,y,z])
	{
		cube(1, center = center);
	}
}

module cone(radius = 10, height = 20, center = false)
{
	cylinder(height, radius, 0, center = center);
}

module tube(outer = 20, inner = 10, height = 100, center = false)
{
	difference()
	{
		cylinder(r = outer, h = height, center = center);
		cylinder(r = inner, h = height, center = center);
	}
}

module pyramid(width = 20, height = 20)
{
	polyhedron(
		points = [
			[width, 0, 0],
			[0, width, 0],
			[-width, 0, 0],
			[0, -width, 0],
			[0, 0, height]
		],
		triangles = [
			[0, 1, 2, 3],
			[4, 1, 0],
			[4, 2, 1],
			[4, 3, 2],
			[4, 0, 3]
		]
	);
}

module wedge(width = 10, height = 20, depth = 30)
{
	rotate([0, -90, 0])
	{
	polyhedron(
		points = [
			[0, 0, 0],
			[height, 0, 0],
			[0, width, 0],
			[0, 0, depth],
			[height, 0, depth],
			[0, width, depth]
		],
		triangles = [
			[0,1,2],
			[5,4,3],
			[3,4,1,0],
			[0,2,5,3],
			[4,5,2,1]
		]
	);
	}
}

module cross(width = 30, thickness = 10, depth = 5)
{
	union()
	{
		box(thickness, width, depth, center = true);
		box(width, thickness, depth, center = true);
	}
}

module stem()
{
	union()
	{
		intersection()
		{
			cylinder(60, 7, 7);
			translate([0,0,20])
			{
				cross(15, 5, 40);
			}
		}

		translate([0, 0, 40*2-21])
		{
			rotate([180, 0, 0])
			{
				intersection()
				{
					cylinder(30, 20, 5);
					translate([0,0,15])
					{
						cross(40, 5, 30);
					}
				}
			}
		}
	}
}

module cup()
{
	scale([1,1,1.3])
	{
		difference()
		{
			sphere(25);
			translate([0, 0, 40])
			{
				cube(50, true);
			}
			sphere(21.5);
		}
	}
}

module base()
{
	union()
	{
		cylinder(4, 20, 20);
		translate([0, 0, 4])
		{
			scale([0.2, 0.2, 0.04])
			{
				sphere(100);
			}
		}
	}
}

module wineglass()
{

		difference()
		{
			union()
			{
				stem();
				base();
			}
			translate([0, 0, 40*2.45-20])
			{
				scale([1,1,1.3])
				{
					sphere(23.5);
				}
			}
			translate([-25,-25, 55])
				cube(50,false);
		}

}
//translate([40, 0, 0])
//cube(60,false);
//wineglass();
translate([0,0,40*2.45-20])
cup();