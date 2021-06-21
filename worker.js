onmessage = function(e) {
    msg = e.data;
    if (msg[0]==="mount"){
        let start = performance.now();
        const f = e.data[1];
        FS.mount(WORKERFS, { files: [f] }, '/work');
        let res = Module.surfaceReader('/work/' + f.name,"pmd");
        let end = performance.now();
        console.log("wasm",(end- start)*0.001,"s");
        let arr = []
        for (var i = 0; i < res.size(); i++) {
            arr.push(res.get(i));
        }
        end = performance.now();
        console.log("total",(end- start)*0.001,"s");
        console.log(arr);
        surf = {ncol:arr[0],nrow:arr[1],Xstep:arr[2],Ystep:arr[3],
                origX:arr[4],origY:arr[5],undef:arr[6],data:arr.slice(7,arr.length)}
        console.log(surf);
    }
}

self.importScripts('pmread.js');
FS.mkdir('/work');