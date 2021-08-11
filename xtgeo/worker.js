import {Module,FS,WORKERFS} from "./pmread.js";
self.onmessage = function(e) {
    let msg = e.data;
    if (msg[0]==="mount"){
        const f = e.data[1];
        FS.mkdir('/work');
        FS.mount(WORKERFS, { files: [f] }, '/work');
        let res = Module.surfaceReader('/work/' + f.name,"pmd");
        let arr = []
        //vector to arr
        for (var i = 0; i < res.size(); i++) {
            arr.push(res.get(i));
        }
        FS.unmount('/work')
        let params={}
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
            x_org +=arr[3]
        }
        arr = arr.slice(7,arr.length)
        params.data.z = [];
        while(arr.length) params.data.z.push(arr.splice(0,params.data.y.length));
        console.log(params)
    }
}

//append export  {Module,FS,WORKERFS} to pmread.js