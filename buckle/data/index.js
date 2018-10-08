const FEATURES = document.querySelector("#features");
const FEATURE = document.querySelector("#feature");

function showError(e) {
	alert(e.message);
}

function setFeature(feature, options = {}) {
	FEATURE.innerHTML = "";
	FEATURE.dataset.feature = feature;

	if (!options.readOnly) { fetch(`/feature?feature=${encodeURIComponent(feature)}`, {method:"POST"}).catch(showError); }

	let controller = window[feature];
	controller && controller(FEATURE);
}

function buildFeature(feature, label) {
	let button = document.createElement("button");
	button.textContent = label;
	button.addEventListener("click", e => setFeature(feature));
	return button;
}

function paintbrush(parent) {
	let color = document.createElement("input");
	color.type = "color";

	function saveOne(offset) {
		let num = parseInt(color.value.slice(1), 16);
		let fd = new FormData();
		fd.set("offset", offset);
		fd.set("r", num >> 16);
		fd.set("g", (num >> 8) & 0xff);
		fd.set("b", num & 0xff);
		fetch("/config", {method:"POST", body:fd});
	}

	function buildOne(r, g, b, offset) {
		let node = document.createElement("span");
		parent.appendChild(node);
		node.style.backgroundColor = `rgb(${r}, ${g}, ${b})`;
		node.addEventListener("click", e => {
			node.style.backgroundColor = color.value;
			saveOne(offset);
		});
	}

	function buildAll(data) {
		let view = new Uint8Array(data);
		let i=0;
		while (i < view.length) {
			let r = view[i+0];
			let g = view[i+1];
			let b = view[i+2];
			buildOne(r, g, b, i);
			i+=3;
		}
		parent.appendChild(color);
	}
	fetch("/config").then(response => response.arrayBuffer()).then(buildAll);
}

FEATURES.appendChild(buildFeature("noop", "No-op"));
FEATURES.appendChild(buildFeature("blinker", "Blinker"));
FEATURES.appendChild(buildFeature("paintbrush", "Paintbrush"));

fetch("/feature").then(response => response.text()).then(feature => setFeature(feature, {readOnly:true}));
