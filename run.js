
function init_plot() {
 //check WebGL
 
 function webGLCheck(){
	let canvas_test = document.createElement("canvas");
	let gl = canvas_test.getContext("webgl") || canvas_test.getContext("experimental-webgl");
	if (!(gl && gl instanceof WebGLRenderingContext)) {
		let div_html = "";
		if (params.hasOwnProperty("fallback_image")) {
			div_html = "<img src=\"" + params.fallback_image + "\">";
		} else {
			div_html = "Sorry, you do not have WebGL enabled.";
		}
		let div = document.getElementById(plot_div_id);
		div.innerHTML = div_html;
	} 
 }

 var plot_div_id = "div_plot_area";
 webGLCheck()

 var canvas = document.createElement("canvas");
 let parent_div = document.getElementById(plot_div_id)
 let file_div = document.createElement("div");
 parent_div.appendChild(file_div);
 parent_div.appendChild(canvas);
 

var graph_created = false


	//dir picker

	var w = new Worker('./worker.js',{ type: "module" });
    let dirpicker = document.createElement("button");
	dirpicker.innerHTML = "Open Directory";
	file_div.appendChild(dirpicker);
	var pmd_list_div = document.createElement('div');
	file_div.appendChild(pmd_list_div)
	dirpicker.onclick = async function getDir() {
		const dirHandle = await window.showDirectoryPicker();
		pmd_list_div.innerHTML=""
		var pmd_files = []
		for await (const f of dirHandle.values()){
			if (f.kind==="file" && f.name.includes(".pmd")){
				pmd_files.push(f.name)
				let checkBox = document.createElement("input");
				var label = document.createElement("label");
				checkBox.type = "checkbox";
				checkBox.value = f.name;
				checkBox.id = f.name;
				pmd_list_div.appendChild(checkBox);
				pmd_list_div.appendChild(label);
				label.appendChild(document.createTextNode(f.name));
				checkBox.onclick = async()=>{
					if (checkBox.checked){
						let first_file_handle = await dirHandle.getFileHandle(checkBox.value)
						let f =  await first_file_handle.getFile()
						new_surf(f)
					} else {
						w.postMessage({remove_surf:checkBox.value})
						
					}
				}
			}
		}
	  }

	//add slider
	var ve = 2;
	let slider = document.getElementById("slider");
	slider.value=ve
	let sliderVal = document.createElement("sliderVal")
	slider.oninput= function(){
		sliderVal.innerHTML=this.value;
		w.postMessage({VE:this.value})
	}
	sliderVal.innerHTML=slider.value

	//2d
	let view2d = document.createElement("button");
	view2d.innerHTML = "2D view";
	file_div.appendChild(view2d);
	view2d.onclick = async function setView2d() {
		w.postMessage({ view2D: view2d.innerHTML })
	}
	//resize
	window.addEventListener('resize', () => { w.postMessage({ events_name: "windowResize", size: { height: window.innerHeight, width: window.innerWidth } }) });

	file_div.appendChild(slider);
	file_div.appendChild(sliderVal)
	w.onmessage =function (event) {
		if (event.data.view === '2D'){
			view2d.innerHTML="3D view"
		}
		if (event.data.view === '3D'){
			view2d.innerHTML="2D view"
		}
	}

	  function new_surf(file){
		  if (!graph_created){
			var plot = {}
			//plot.showing_mesh = false;
			plot.mouseover = true;
			plot.mouseout=true;
			plot.showing_mesh = false; //show grid mesh on surface
			plot.plot_type = "surface";
			plot.width = 1000
			plot.height = 1000
			let slider = document.getElementById("slider");
			plot.ve=slider.value
			//var parent_div = document.getElementById(plot_div_id);
		
			plot.pixelRatio=window.devicePixelRatio ? window.devicePixelRatio : 1;
	
			var offscreen = canvas.transferControlToOffscreen();
			let params = {};
			params.color_scale = "plasma"
			params.file = file
			params.name = file.name
			w.postMessage({canvas:offscreen,plot:plot,params:params}, [offscreen]);
			addMouseCanvas()
			graph_created = true
		  } else {
			let params = {};
			params.color_scale = "plasma"
			params.file = file
			params.name = file.name
			w.postMessage({add_surf:params})
		  }
	  }
	  




 function addMouseCanvas(){
	var mouse_events = ['mousedown', 'mouseup','mouseout','mousemove','wheel','touchstart','touchmove','touchend']
	mouse_events.forEach((events_name)=>{
		canvas.addEventListener(events_name, (e)=>{
			w.postMessage({
				events_name,
				event:{
					clientX: e.clientX,
					clientY: e.clientY,
					deltaY:e.deltaY,
					type: e.type,
					button:e.button,
					ctrlKey:e.ctrlKey,
					shiftkey:e.shiftkey,
					bounding_rect:canvas.getBoundingClientRect()
				}
			})
		})
	})
 }

  }
  
init_plot();
