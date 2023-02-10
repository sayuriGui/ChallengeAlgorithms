let x1 = 0;
let y1 = 0;
let x2 = 0;
let y2 = 0;

let pt1x = 0;
let pt1y = 0;
let pt2x = 0;
let pt2y = 0;

let isDrawing = true;
let pointCount = 0;


function setup() {
    createCanvas(400, 400);
}

function draw() {
    background(255);
    if (x1 != 0 && y1 != 0 && x2 != 0 && y2 != 0 && pointCount != 2) {
        line(x1, y1, x2, y2);
    }
    if (!isDrawing) {
        if (pt1x != 0 && pt1y != 0 ) {
            circle(pt1x, pt1y, 10);
        }
        if (pt2x != 0 && pt2y != 0 ) {
            circle(pt2x, pt2y, 10);
        }
        if (pointCount == 2) {
            noFill();
            bezier(x1, y1, pt1x, pt1y, pt2x, pt2y, x2, y2);
        }
    }
}

function mousePressed() {
    if (isDrawing) {
        x1 = mouseX;
        y1 = mouseY;
        x2 = mouseX;
        y2 = mouseY;
    } else {
        if (pt1x == 0 && pt1y == 0 && pointCount == 0) {
            pt1x = mouseX;
            pt1y = mouseY;
            pointCount++;

        }
        else if (pt2x == 0 && pt2y == 0 && pointCount == 1) {
            pt2x = mouseX;
            pt2y = mouseY;
            pointCount++;
        }
        else {
            if (dist(pt1x, pt1y, mouseX, mouseY) < 30) {
                pt1x = mouseX;
                pt1y = mouseY;
            }
            else if (dist(pt2x, pt2y, mouseX, mouseY) < 30) {
                pt2x = mouseX;
                pt2y = mouseY;
            }
        }
    }

}

function mouseReleased() {
    if (isDrawing) {
        x2 = mouseX;
        y2 = mouseY;
        isDrawing = false;
    }
}

function mouseDragged() {
    if (isDrawing) {
        x2 = mouseX;
        y2 = mouseY;
    }
}

function keyPressed() {
    if (keyCode === ENTER) {
        isDrawing = true;
        x1 = 0;
        y1 = 0;
        x2 = 0;
        y2 = 0;
        pt1x = 0;
        pt1y = 0;
        pt2x = 0;
        pt2y = 0;
        pointCount = 0;
    }
}