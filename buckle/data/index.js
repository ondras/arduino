const FEATURES = document.querySelector("#features");
const FEATURE = document.querySelector("#feature");

FEATURES.appendChild(buildFeature("clear", "Clear"));
FEATURES.appendChild(buildFeature("brightness", "Brightness"));
FEATURES.appendChild(buildFeature("paintbrush", "Paintbrush"));
FEATURES.appendChild(buildFeature("heart", "Heart"));
FEATURES.appendChild(buildFeature("image", "Image"));
FEATURES.appendChild(buildFeature("arrow", "Arrow"));
FEATURES.appendChild(buildFeature("tetris", "Tetris"));

function renderLeds(parent) {
	parent.innerHTML = "";
	let all = document.createElement("section");
	all.classList.add("grid", "leds");
	parent.appendChild(all);

	function buildOne(r, g, b, offset) {
		let node = document.createElement("span");
		node.dataset.offset = offset;
		node.style.backgroundColor = `rgb(${r}, ${g}, ${b})`;
		return node;
	}

	function buildAll(data) {
		let leds = [];
		let view = new Uint8Array(data);
		let i=0;
		while (i < view.length) {
			let r = view[i+0];
			let g = view[i+1];
			let b = view[i+2];
			let node = buildOne(r, g, b, i);
			all.appendChild(node);
			leds.push(node);
			i+=3;
		}
		return leds;
	}

	return fetch("/config").then(response => response.arrayBuffer()).then(buildAll);	
}

function showError(e) {
	alert(e.message);
}

function postConfig(data) {
	let fd = new FormData();
	for (let p in data) { fd.set(p, data[p]); }
	return fetch("/config", {method:"POST", body:fd});
}

function setFeature(feature, options = {}) {
	FEATURE.innerHTML = "";

	Array.from(FEATURES.querySelectorAll("button")).forEach(button => {
		button.classList.toggle("active", button.dataset.feature == feature);
	});

	if (!options.readOnly) { fetch(`/feature?feature=${encodeURIComponent(feature)}`, {method:"POST"}).catch(showError); }

	let controller = window[feature];
	controller && controller(FEATURE);
}

function buildFeature(feature, label) {
	let button = document.createElement("button");
	button.dataset.feature = feature;
	button.textContent = label;
	button.addEventListener("click", e => setFeature(feature));
	return button;
}

function paintbrush(parent) {
	let color = document.createElement("input");
	color.type = "color";

	function save(offset) {
		let num = parseInt(color.value.slice(1), 16);
		postConfig({
			offset,
			r: num >> 16,
			g: (num >> 8) & 0xff,
			b: num & 0xff
		});
	}

	renderLeds(parent).then(leds => {
		leds.forEach(led => {
			led.addEventListener("click", e => {
				led.style.backgroundColor = color.value;
				save(led.dataset.offset);
			});
		});
		parent.appendChild(color);
	});
}

function image(parent) {
	let images = document.createElement("section");
	images.classList.add("grid", "buttons");
	let current = document.createElement("div");

	function setImage(image) {
		postConfig({image}).then(r => r.text()).then(() => renderLeds(current));
	}

	["flag", "smile"].forEach(image => {
		let button = document.createElement("button");
		button.textContent = image;
		button.addEventListener("click", e => setImage(image));
		images.appendChild(button);
	});

	parent.appendChild(images);
	parent.appendChild(current);
}

function arrow(parent) {
	let color = document.createElement("input");
	color.type = "color";

	const arrows = {
		"↑": 0,
		"→": 1,
		"↓": 2,
		"←": 3
	};

	function save(orientation) {
		let num = parseInt(color.value.slice(1), 16);
		postConfig({
			orientation,
			r: num >> 16,
			g: (num >> 8) & 0xff,
			b: num & 0xff
		});
	}

	let buttons = document.createElement("section");
	buttons.classList.add("grid", "buttons");
	parent.appendChild(buttons);
	Object.keys(arrows).forEach(arrow => {
		let button = document.createElement("button");
		button.classList.add("arrow");
		button.textContent = arrow;
		button.addEventListener("click", e => save(arrows[arrow]));
		buttons.appendChild(button);
	});

	parent.appendChild(color);
}

function tetris(parent) {
	let times = [30, 50, 100, 200];

	function setDelay(delay) {
		postConfig({delay});
	}

	function buildSelect(current) {
		let select = document.createElement("select");
		current = Number(current);
		if (!(times.includes(current))) { times.push(current); }
		times.forEach(time => {
			let option = document.createElement("option");
			option.value = time;
			option.textContent = time;
			select.appendChild(option);
		});
		select.value = current;
		parent.appendChild(select);
		select.addEventListener("change", e => setDelay(select.value));
	}

	return fetch("/config").then(response => response.text()).then(buildSelect);
}

function brightness(parent) {
	let current = document.createElement("span");
	parent.appendChild(current);

	let input = document.createElement("input");
	input.type = "range";
	input.min = 10;
	input.max = 200;
	input.step = 10;
	parent.appendChild(input);

	function sync() { current.textContent = input.value; }

	input.addEventListener("input", e => {
		sync();
		postConfig({brightness: input.value});
	})

	return fetch("/config").then(response => response.text()).then(value => {
		input.value = value;
		sync();
	});
}

fetch("/feature").then(response => response.text()).then(feature => setFeature(feature, {readOnly:true}));
