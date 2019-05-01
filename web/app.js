var chart = null;
var m_canvas = null;
var EXECUTING = false
var CHART_CLEARED = true;

function send_error(msg) {
    alert(msg)
}

function setupGraph(graph_labels, graph_values) {
    var multiplier = 30;

    if (window.innerWidth >= 768) {
        multiplier = 8;
        if (graph_labels.length < 20) {
            multiplier = 12;
        }
        if (graph_labels.length > 200) {
            multiplier = 5;
        }
    } else {
        multiplier = 15;
        if (graph_labels.length < 5) {
            multiplier = 50;
        }
        else if (graph_labels.length < 10) {
            multiplier = 30;
        }
        else if (graph_labels.length < 20) {
            multiplier = 20;
        }
        else if (graph_labels.length > 200) {
            multiplier = 10;
        }
    }

    m_canvas.setAttribute("height", graph_labels.length * multiplier + "px")

    chart = new Chart(ctx, {
        type: 'horizontalBar',
        data: {
            labels: graph_labels,
            datasets: [{
                label: 'Probablistic amplitude.',
                backgroundColor: 'rgb(0, 98, 204)',
                borderColor: 'rgb(36, 49, 56)',
                data: graph_values
            }]
        },
        options: {
            responsive: true,
            legend: {
                display: false
            },
            scales: {
                xAxes: [{
                    ticks: {
                        suggestedMin: 0,
                        suggestedMax: 1
                    }
                }]
            }
        }
    });
    CHART_CLEARED = false;
}

$(document).ready(function () {

    m_canvas = document.getElementById('myChart');
    ctx = m_canvas.getContext('2d');

    $('#main_form').on('submit', function (e) {
        e.preventDefault();
        $("#exec_status").empty();
        $(".err_ct").text("0");
        $(".warn_ct").text("0");

        var final_code = $("#m_code").val().trim().toUpperCase();

        if (EXECUTING) {
            send_error("Execution in progress. Please wait.");
            return
        }
        if (!final_code) {
            send_error("Please enter code to continue.");
            return;
        }

        EXECUTING = true;
        $("#m_code").val(final_code)
        $("#exec_res").text("Waiting for execution");

        if (window.innerWidth < 768) {
            setTimeout(function () {
                var offset = 0;
                offset = $("#report_div").offset().top;
                $('html, body').animate({
                    scrollTop: offset
                }, 300);
            }, 600);
        }

        if (chart != null && !CHART_CLEARED) {
            chart.clear();
            chart.destroy();
            CHART_CLEARED = true;
        }

        $("#sendbtn").fadeOut("slow");

        $('#resluts').html("<h2>N/A</h2> <small>Executing please wait..</small>");
        $.post("", $("#main_form").serialize(), function (data) {
            var resluts = data.split("====================================================");
            // GENERATE PROBABILITY DENSITY GRAPH
            var densities = resluts[3].split('\n');
            var graph_labels = [];
            var graph_values = [];
            densities.forEach(function (element) {
                if (element.trim() != "") {
                    key_pair = element.split(" => ");
                    graph_labels.push(key_pair[0]);
                    graph_values.push(key_pair[1]);
                }
            });

            if (graph_labels.length > 0) {
                setupGraph(graph_labels, graph_values);
            }


            $('#resluts').html("<h2>" + resluts[4].trim() + "</h2> <small>Measured Output</small>");
            $("#exec_res").text(resluts[0]);

            if (resluts[1].trim()) {
                $(".warn_ct").text((resluts[1].match("/\n/g") || '').length + 1)
                $("#exec_status").append('<div class="alert alert-warning">' + resluts[1] + '</div>')
            }
            if (resluts[2].trim()) {
                $(".err_ct").text((resluts[2].match("/\n/g") || '').length + 1)
                $("#exec_status").append('<div class="alert alert-danger">' + resluts[2] + '</div>')
            }



        }).always(function () {
            EXECUTING = false;
            $("#sendbtn").fadeIn("slow");
        });
    });
});
