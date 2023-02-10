let clickCount = 0;

let flistPoints = [120, 40, 320, 20, 320, 300, 330, 300];
let slistPoints = [330, 300, 330, 94, 380, 58, 600, 40];

function setup() {
    createCanvas(800, 400);
    frameRate(1)
}

function draw() {
    background(220);
    noFill();
    if (clickCount == 1) {
        // Click 1 - trajectory
        //Define and draw your ball's trajectory and draw it. You can use 2 curves, one that is going down and one that is going up.
        bezier(flistPoints[0], flistPoints[1], flistPoints[2], flistPoints[3], flistPoints[4], flistPoints[5], flistPoints[6], flistPoints[7]);
        bezier(slistPoints[0], slistPoints[1], slistPoints[2], slistPoints[3], slistPoints[4], slistPoints[5], slistPoints[6], slistPoints[7]);
    }
    else if (clickCount == 2) {
        // Click 2 - storyboard
        // Draw a summary of your storyboard based on figures 4 and 5. Only draw some selected frames that will provide a glimpse of your animation.
        storyboard(flistPoints[0], flistPoints[1], flistPoints[2], flistPoints[3], flistPoints[4], flistPoints[5], flistPoints[6], flistPoints[7]);
        storyboard(slistPoints[0], slistPoints[1], slistPoints[2], slistPoints[3], slistPoints[4], slistPoints[5], slistPoints[6], slistPoints[7]);
    }
    else if (clickCount == 3) {
        // Click 3 - animation
        // Run your ball-bouncing simulation. Your ball will follow the pre-defined curved trajectories. Your ball will be deformed as it's going down/up.
        animation(flistPoints, slistPoints);
    }
}

function storyboard(x1, y1, x2, y2, x3, y3, x4, y4) {
    fill(255);
    steps = 10;
    for (i = 0; i <= steps; i++) {
        t = i / float(steps);
        x = bezierPoint(x1, x2, x3, x4, t);
        y = bezierPoint(y1, y2, y3, y4, t);
        ellipse(x, y, 10, 10);
    }
}

async function animation(curv1, curv2) {
    fill (255);
    steps = 10;
    for (i = 0; i <= steps; i++) {
        await sleep(1000);
        t = i / float(steps);
        x = bezierPoint(flistPoints[0], flistPoints[2], flistPoints[4], flistPoints[6], t);
        y = bezierPoint(flistPoints[1], flistPoints[3], flistPoints[5], flistPoints[7], t);
        ellipse(x, y, 10, 10);
    }
    for (i = 0; i <= steps; i++) {
        await sleep(1000);
        t = i / float(steps);
        x = bezierPoint(slistPoints[0], slistPoints[2], slistPoints[4], slistPoints[6], t);
        y = bezierPoint(slistPoints[1], slistPoints[3], slistPoints[5], slistPoints[7], t);
        ellipse(x, y, 10, 10);
    }
  }

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

function mouseClicked() {
    if (clickCount == 0) {
        console.log ("Click 1 - trajectory");
        clickCount++;
    }
    else if (clickCount == 1) {
        console.log ("Click 2 - storyboard");
        clickCount++;
    }
    else if (clickCount == 2) {
        console.log ("Click 3 - animation");
        clickCount++;
    }
    else {
        console.log ("Click 4 - end");
        clickCount = 0;
    }

}