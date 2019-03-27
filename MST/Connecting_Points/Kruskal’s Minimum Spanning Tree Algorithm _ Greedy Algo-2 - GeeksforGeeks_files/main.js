animate();

//Function: Animate runs when Enabler has initialized
function animate() {

  $(".overlay").fadeOut(1000);

  
  // HOUSE text fades in
  setTimeout(function() {
    
    $(".s2").fadeIn(1000);
  }, 500);

  // HOUSE text slides up
  setTimeout(function() {
    
    $(".s2").addClass("slideUp");
  }, 2000);

  // ART text fades in
  setTimeout(function() {
    
    $(".s3").fadeIn(1000);
  }, 2500);

  // b&w becomes color
  setTimeout(function() {
    $(".slide2").fadeIn(1000);
}, 2500);

  setTimeout(function() {
    $(".slide1").fadeOut(1000);
}, 3500);

  // color fades
  setTimeout(function() {
    $(".slide2").addClass("faded")
}, 4500);

  // fade out words
  setTimeout(function() {
    $(".hideBox").fadeTo( "slow", 0.00 );
    
}, 4500);

  // logo fade in
  setTimeout(function() {
    $(".s4").fadeIn(1000);
}, 5500);

  // box fade in
  setTimeout(function() {
    $(".s7").fadeIn(1000);
}, 6000);

  // cta fade in
  setTimeout(function() {
    $(".s5").fadeIn(1000);
}, 6500);

  // cta fade in
  setTimeout(function() {
    $(".s6").fadeIn(1000);
}, 6500);






 


} //end animate

 