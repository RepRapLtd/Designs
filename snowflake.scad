scale( [0.5, 0.5, 0.5] ) {

    union() {
        for( i = [0:5] ) {
            rotate( i*60, [0,0,1]) {
                      
             
             difference() {
                 translate( [-5,45,-5]) {
                        rotate( 60, [0,0,1]) {
                            translate( [-5, -5, 0] ) {
                                cube(size = [10,25,10]);
                            }
                        }
                }
                    
                translate( [-25,45,-6]) {
                    cube(size= [10,40,12]);
                }
             }
             
             difference() {
                translate( [5,45,-5]) {
                        rotate( -60, [0,0,1]) {
                            translate( [-5, -5, 0] ) {
                                cube(size = [10,25,10]);
                            }
                        }
                 }
                    
                translate( [15,45,-6]) {
                    cube(size= [10,40,12]);
                }
             }

                 difference() {
              translate( [-5,25,-5]) {
                        rotate( 60, [0,0,1]) {
                            translate( [-5, -5, 0] ) {
                                cube(size = [10,30,10]);
                            }
                        }
                }
                
                translate( [-34,15,-6]) {
                    cube(size= [10,40,12]);
                }
                
           }
                

            difference() {
              translate( [5,25,-5]) {
                    rotate( -60, [0,0,1]) {
                        translate( [-5, -5, 0] ) {
                            cube(size = [10,30,10]);
                        }
                    }
              }         
             
                 translate( [24,20,-6]) {
                    cube(size= [10,40,12]);
                }
             }
               
               
              

            
                translate( v=[-5,0,-5]) {
                   cube(size = [10,60,10]);
                }
            }
        }

    }
}