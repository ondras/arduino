$fn = 80;
inner = 6.5;
thickness=0.6;
height = 1.0;
belt = 4.2;
holder_r = 0.35 / 2;
holder_z = -1.3;
pin_r = 0.3 / 2;
pin_length = 1.5;
pin_head_offset = 0.3;
pin_thickness = thickness/2.7;
glass_size = inner + 2*0.2;
glass_height = 0.25;

outer = inner + 2*thickness;
rounded = 0.2;

module box() {
    o = outer-2*rounded;
    minkowski() {
        cube([o, o, height-2*rounded], center=true);
        sphere(r=rounded);
    };
}

module holder_ball_small(offset_y) {
    offset_x = -(inner + thickness)/2 + holder_z/2;
    offset_z = holder_z;
    translate([offset_x, offset_y, offset_z])
      sphere(r=holder_r);
}

module holder_ball_large(offset_y) {
    offset_x = -(inner + thickness)/2;
    offset_z = 0;
    translate([offset_x, offset_y, offset_z])
      sphere(r=thickness/2);
}

module holder() {
    leg_r2 = thickness/2;
    dist = belt/2 +leg_r2;

    hull() {
        holder_ball_small(-dist);
        holder_ball_small(dist);
    }
    hull() {
        holder_ball_small(-dist);
        holder_ball_large(-dist);
    }
    hull() {
        holder_ball_small(dist);
        holder_ball_large(dist);
    }
}

module pin_ball_large() {
    offset_x = (inner+thickness)/2;
    translate([offset_x, 0, -height/4])
      sphere(r=pin_thickness);
}

module pin_ball_small(r=pin_r) {
    offset_x = (inner+thickness)/2;
    translate([offset_x - pin_head_offset, 0, -pin_length])
      sphere(r);
}

module pin() {
    hull() {
        pin_ball_large();
        pin_ball_small();
    }
    pin_ball_small(r=pin_r*1.3);
}

module main() {
    difference() {
      union() {
        box();
        holder();
        pin();
      }
      cube([inner, inner, height], center=true);
      translate([0, 0, (height-glass_height)/2])
        cube([glass_size, glass_size, glass_height], center=true);
    }
}    

module print() {
    rotate(a=[180, 0, 0])
    scale([10, 10, 10])
        children();
}

print() main();
