$(document).ready(function() {
	// 滚动窗口来判断按钮显示或隐藏
	$(window).scroll(function() {
		if ($(this).scrollTop() > 150) {
			$('.back-to-top').fadeIn(100);
		} else {
			$('.back-to-top').fadeOut(100);
		}
	});
	
	// jQuery实现动画滚动
	$('.back-to-top').click(function(event) {
		event.preventDefault();
		$('html, body').animate({scrollTop: 0}, 500);
	})
});