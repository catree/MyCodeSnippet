function init(){
    var map = new AMap.Map('container', {
        center: [113.846118,22.709236],
        zoom: 16
    });
    map.plugin(["AMap.ToolBar"], function() {
        map.addControl(new AMap.ToolBar());
    });
}