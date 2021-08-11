import three_d from './three_d/three_d.js';
import {Module,FS,WORKERFS} from "./xtgeo/xtgeo.js";
var plot
FS.mkdir('/work');
self.onmessage = function (event) {
    if (event.data.canvas){
        var canvas = event.data.canvas;
        plot = event.data.plot;
        let params = event.data.params
        let f = params.file
        console.log(f,params)
        readFile(f,params)
        three_d.make_surface(plot,params,canvas);
    }
    if (event.data.events_name === 'mousedown'){
        three_d.mouse_down_fn(event.data.event,plot)
    }
    if (event.data.events_name === 'mouseup'){
        three_d.mouse_up_fn(event.data.event,plot,false)
    }
    if (event.data.events_name === 'mouseout'){
        three_d.mouse_up_fn(event.data.event,plot,true)
        three_d.mouse_out_wrapper(plot, [-1, -1], true)
    }
    if (event.data.events_name === 'wheel'){
        three_d.mouse_zoom_wrapper(event.data.event,plot)
    }
    if (event.data.events_name === 'mousemove'){
        three_d.mouse_move_wrapper(event.data.event,plot)
    }
    if (event.data.add_surf){
        let surf_params = event.data.add_surf
        let f = surf_params.file
        readFile(f,surf_params)
        three_d.add_surface(plot,surf_params)
    }
    if (event.data.remove_surf){
        let surf_to_remove = event.data.remove_surf
        three_d.remove_surface(plot,surf_to_remove)
    }
}

function readFile(f,params){
        //FS.mkdir('/work');
        FS.mount(WORKERFS, { files: [f] }, '/work');
        let res = Module.surfaceReader('/work/' + f.name,"pmd");
        let arr = []
        //vector to arr
        for (var i = 0; i < res.size(); i++) {
            arr.push(res.get(i));
        }
        params.data={}
        params.data.x = []
        params.data.y = []
        let x_org = arr[4]
        for (let i = 0;i<arr[0];i++){
            params.data.x.push(x_org)
            x_org +=arr[2]
        }
        let y_org = arr[5]
        for (let i = 0;i<arr[1];i++){
            params.data.y.push(y_org)
            y_org +=arr[3]
        }
        arr = arr.slice(7,arr.length)
        params.data.z = [];
        while(arr.length) params.data.z.push(arr.splice(0,params.data.y.length));
        FS.unmount('/work')
}