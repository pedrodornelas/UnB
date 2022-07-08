#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# SPDX-License-Identifier: GPL-3.0
#
# GNU Radio Python Flow Graph
# Title: AR01
# Author: pedro
# GNU Radio version: 3.8.1.0

from distutils.version import StrictVersion

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print("Warning: failed to XInitThreads()")

from PyQt5 import Qt
from gnuradio import qtgui
from gnuradio.filter import firdes
import sip
from gnuradio import analog
from gnuradio import blocks
from gnuradio import channels
from gnuradio import filter
from gnuradio import gr
import sys
import signal
from argparse import ArgumentParser
from gnuradio.eng_arg import eng_float, intx
from gnuradio import eng_notation
from gnuradio.qtgui import Range, RangeWidget
from gnuradio import qtgui

class m180108140_Exp07_AR01(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "AR01")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("AR01")
        qtgui.util.check_set_qss()
        try:
            self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
        except:
            pass
        self.top_scroll_layout = Qt.QVBoxLayout()
        self.setLayout(self.top_scroll_layout)
        self.top_scroll = Qt.QScrollArea()
        self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
        self.top_scroll_layout.addWidget(self.top_scroll)
        self.top_scroll.setWidgetResizable(True)
        self.top_widget = Qt.QWidget()
        self.top_scroll.setWidget(self.top_widget)
        self.top_layout = Qt.QVBoxLayout(self.top_widget)
        self.top_grid_layout = Qt.QGridLayout()
        self.top_layout.addLayout(self.top_grid_layout)

        self.settings = Qt.QSettings("GNU Radio", "m180108140_Exp07_AR01")

        try:
            if StrictVersion(Qt.qVersion()) < StrictVersion("5.0.0"):
                self.restoreGeometry(self.settings.value("geometry").toByteArray())
            else:
                self.restoreGeometry(self.settings.value("geometry"))
        except:
            pass

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 64000
        self.n_bits = n_bits = 4

        ##################################################
        # Blocks
        ##################################################
        self._n_bits_range = Range(1, 16, 1, 4, 200)
        self._n_bits_win = RangeWidget(self._n_bits_range, self.set_n_bits, 'n_bits', "counter_slider", float)
        self.top_grid_layout.addWidget(self._n_bits_win, 2, 1, 1, 2)
        for r in range(2, 3):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(1, 3):
            self.top_grid_layout.setColumnStretch(c, 1)
        self.qtgui_time_sink_x_0 = qtgui.time_sink_f(
            256, #size
            samp_rate, #samp_rate
            'Osciloscópio', #name
            4 #number of inputs
        )
        self.qtgui_time_sink_x_0.set_update_time(0.10)
        self.qtgui_time_sink_x_0.set_y_axis(-1, 1)

        self.qtgui_time_sink_x_0.set_y_label('Amplitude', 'V')

        self.qtgui_time_sink_x_0.enable_tags(True)
        self.qtgui_time_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, 0, "")
        self.qtgui_time_sink_x_0.enable_autoscale(False)
        self.qtgui_time_sink_x_0.enable_grid(True)
        self.qtgui_time_sink_x_0.enable_axis_labels(True)
        self.qtgui_time_sink_x_0.enable_control_panel(True)
        self.qtgui_time_sink_x_0.enable_stem_plot(False)


        labels = ['Mensagem', 'Quantizado', 'Recuperado', 'Ruído', 'Signal 5',
            'Signal 6', 'Signal 7', 'Signal 8', 'Signal 9', 'Signal 10']
        widths = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        colors = ['blue', 'red', 'green', 'black', 'cyan',
            'magenta', 'yellow', 'dark red', 'dark green', 'dark blue']
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]
        styles = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        markers = [-1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1]


        for i in range(4):
            if len(labels[i]) == 0:
                self.qtgui_time_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_time_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_time_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_time_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_time_sink_x_0.set_line_style(i, styles[i])
            self.qtgui_time_sink_x_0.set_line_marker(i, markers[i])
            self.qtgui_time_sink_x_0.set_line_alpha(i, alphas[i])

        self._qtgui_time_sink_x_0_win = sip.wrapinstance(self.qtgui_time_sink_x_0.pyqwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_time_sink_x_0_win, 3, 1, 6, 1)
        for r in range(3, 9):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(1, 2):
            self.top_grid_layout.setColumnStretch(c, 1)
        self.qtgui_number_sink_0 = qtgui.number_sink(
            gr.sizeof_float,
            0,
            qtgui.NUM_GRAPH_HORIZ,
            2
        )
        self.qtgui_number_sink_0.set_update_time(0.10)
        self.qtgui_number_sink_0.set_title('')

        labels = ['RSR', 'Pot(msg)', '', '', '',
            '', '', '', '', '']
        units = ['', '', '', '', '',
            '', '', '', '', '']
        colors = [("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"),
            ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black")]
        factor = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]

        for i in range(2):
            self.qtgui_number_sink_0.set_min(i, -1)
            self.qtgui_number_sink_0.set_max(i, 1)
            self.qtgui_number_sink_0.set_color(i, colors[i][0], colors[i][1])
            if len(labels[i]) == 0:
                self.qtgui_number_sink_0.set_label(i, "Data {0}".format(i))
            else:
                self.qtgui_number_sink_0.set_label(i, labels[i])
            self.qtgui_number_sink_0.set_unit(i, units[i])
            self.qtgui_number_sink_0.set_factor(i, factor[i])

        self.qtgui_number_sink_0.enable_autoscale(False)
        self._qtgui_number_sink_0_win = sip.wrapinstance(self.qtgui_number_sink_0.pyqwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_number_sink_0_win, 1, 1, 1, 2)
        for r in range(1, 2):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(1, 3):
            self.top_grid_layout.setColumnStretch(c, 1)
        self.qtgui_freq_sink_x_0 = qtgui.freq_sink_f(
            4096, #size
            firdes.WIN_BLACKMAN_hARRIS, #wintype
            0, #fc
            samp_rate, #bw
            'Analisador de Espectro', #name
            4
        )
        self.qtgui_freq_sink_x_0.set_update_time(0.10)
        self.qtgui_freq_sink_x_0.set_y_axis(-140, 10)
        self.qtgui_freq_sink_x_0.set_y_label('Relative Gain', 'dB')
        self.qtgui_freq_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, 0.0, 0, "")
        self.qtgui_freq_sink_x_0.enable_autoscale(False)
        self.qtgui_freq_sink_x_0.enable_grid(True)
        self.qtgui_freq_sink_x_0.set_fft_average(1.0)
        self.qtgui_freq_sink_x_0.enable_axis_labels(True)
        self.qtgui_freq_sink_x_0.enable_control_panel(True)


        self.qtgui_freq_sink_x_0.set_plot_pos_half(not True)

        labels = ['Mensagem', 'Quantizado', 'Recuperado', 'Ruido', '',
            '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        colors = ["blue", "red", "green", "black", "cyan",
            "magenta", "yellow", "dark red", "dark green", "dark blue"]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]

        for i in range(4):
            if len(labels[i]) == 0:
                self.qtgui_freq_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_freq_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_freq_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_freq_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_freq_sink_x_0.set_line_alpha(i, alphas[i])

        self._qtgui_freq_sink_x_0_win = sip.wrapinstance(self.qtgui_freq_sink_x_0.pyqwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_freq_sink_x_0_win, 3, 2, 6, 1)
        for r in range(3, 9):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(2, 3):
            self.top_grid_layout.setColumnStretch(c, 1)
        self.low_pass_filter_0 = filter.interp_fir_filter_fff(
            1,
            firdes.low_pass(
                1,
                samp_rate,
                3000,
                500,
                firdes.WIN_HAMMING,
                6.76))
        self.channels_quantizer_0_0 = channels.quantizer(n_bits)
        self.blocks_throttle_0_1_0 = blocks.throttle(gr.sizeof_float*1, samp_rate,True)
        self.blocks_throttle_0_1 = blocks.throttle(gr.sizeof_float*1, samp_rate,True)
        self.blocks_sub_xx_0 = blocks.sub_ff(1)
        self.blocks_rms_xx_1 = blocks.rms_ff(0.0001)
        self.blocks_rms_xx_0_0 = blocks.rms_ff(0.0001)
        self.blocks_rms_xx_0 = blocks.rms_ff(0.0001)
        self.blocks_nlog10_ff_0 = blocks.nlog10_ff(20, 1, 0)
        self.blocks_multiply_xx_0 = blocks.multiply_vff(1)
        self.blocks_divide_xx_0 = blocks.divide_ff(1)
        self.blocks_add_xx_1 = blocks.add_vff(1)
        self.analog_sig_source_x_0_1_0 = analog.sig_source_f(samp_rate, analog.GR_SIN_WAVE, 3000, -0.12, 0, 0)
        self.analog_sig_source_x_0_1 = analog.sig_source_f(samp_rate, analog.GR_SIN_WAVE, 1000, 1.12, 0, 0)



        ##################################################
        # Connections
        ##################################################
        self.connect((self.analog_sig_source_x_0_1, 0), (self.blocks_throttle_0_1, 0))
        self.connect((self.analog_sig_source_x_0_1_0, 0), (self.blocks_throttle_0_1_0, 0))
        self.connect((self.blocks_add_xx_1, 0), (self.blocks_rms_xx_0, 0))
        self.connect((self.blocks_add_xx_1, 0), (self.blocks_rms_xx_1, 0))
        self.connect((self.blocks_add_xx_1, 0), (self.blocks_sub_xx_0, 0))
        self.connect((self.blocks_add_xx_1, 0), (self.channels_quantizer_0_0, 0))
        self.connect((self.blocks_add_xx_1, 0), (self.qtgui_freq_sink_x_0, 0))
        self.connect((self.blocks_add_xx_1, 0), (self.qtgui_time_sink_x_0, 0))
        self.connect((self.blocks_divide_xx_0, 0), (self.blocks_nlog10_ff_0, 0))
        self.connect((self.blocks_multiply_xx_0, 0), (self.qtgui_number_sink_0, 1))
        self.connect((self.blocks_nlog10_ff_0, 0), (self.qtgui_number_sink_0, 0))
        self.connect((self.blocks_rms_xx_0, 0), (self.blocks_divide_xx_0, 0))
        self.connect((self.blocks_rms_xx_0_0, 0), (self.blocks_divide_xx_0, 1))
        self.connect((self.blocks_rms_xx_1, 0), (self.blocks_multiply_xx_0, 1))
        self.connect((self.blocks_rms_xx_1, 0), (self.blocks_multiply_xx_0, 0))
        self.connect((self.blocks_sub_xx_0, 0), (self.blocks_rms_xx_0_0, 0))
        self.connect((self.blocks_sub_xx_0, 0), (self.qtgui_freq_sink_x_0, 3))
        self.connect((self.blocks_sub_xx_0, 0), (self.qtgui_time_sink_x_0, 3))
        self.connect((self.blocks_throttle_0_1, 0), (self.blocks_add_xx_1, 0))
        self.connect((self.blocks_throttle_0_1_0, 0), (self.blocks_add_xx_1, 1))
        self.connect((self.channels_quantizer_0_0, 0), (self.blocks_sub_xx_0, 1))
        self.connect((self.channels_quantizer_0_0, 0), (self.low_pass_filter_0, 0))
        self.connect((self.channels_quantizer_0_0, 0), (self.qtgui_freq_sink_x_0, 1))
        self.connect((self.channels_quantizer_0_0, 0), (self.qtgui_time_sink_x_0, 1))
        self.connect((self.low_pass_filter_0, 0), (self.qtgui_freq_sink_x_0, 2))
        self.connect((self.low_pass_filter_0, 0), (self.qtgui_time_sink_x_0, 2))

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "m180108140_Exp07_AR01")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.analog_sig_source_x_0_1.set_sampling_freq(self.samp_rate)
        self.analog_sig_source_x_0_1_0.set_sampling_freq(self.samp_rate)
        self.blocks_throttle_0_1.set_sample_rate(self.samp_rate)
        self.blocks_throttle_0_1_0.set_sample_rate(self.samp_rate)
        self.low_pass_filter_0.set_taps(firdes.low_pass(1, self.samp_rate, 3000, 500, firdes.WIN_HAMMING, 6.76))
        self.qtgui_freq_sink_x_0.set_frequency_range(0, self.samp_rate)
        self.qtgui_time_sink_x_0.set_samp_rate(self.samp_rate)

    def get_n_bits(self):
        return self.n_bits

    def set_n_bits(self, n_bits):
        self.n_bits = n_bits
        self.channels_quantizer_0_0.set_bits(self.n_bits)



def main(top_block_cls=m180108140_Exp07_AR01, options=None):

    if StrictVersion("4.5.0") <= StrictVersion(Qt.qVersion()) < StrictVersion("5.0.0"):
        style = gr.prefs().get_string('qtgui', 'style', 'raster')
        Qt.QApplication.setGraphicsSystem(style)
    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls()
    tb.start()
    tb.show()

    def sig_handler(sig=None, frame=None):
        Qt.QApplication.quit()

    signal.signal(signal.SIGINT, sig_handler)
    signal.signal(signal.SIGTERM, sig_handler)

    timer = Qt.QTimer()
    timer.start(500)
    timer.timeout.connect(lambda: None)

    def quitting():
        tb.stop()
        tb.wait()
    qapp.aboutToQuit.connect(quitting)
    qapp.exec_()


if __name__ == '__main__':
    main()