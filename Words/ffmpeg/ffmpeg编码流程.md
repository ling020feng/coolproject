```flow

st=>start: av_register_all()

op=>operation: avformat_alloc_output_context2()
op1=>operation: avio_open()
op2=>operation: avcodec_find_encoder()
op3=>operation: avcodec_open2()
op4=>operation: avformat_write_header()
op5=>operation: avcodec_encode_video2()
op6=>operation: av_write_frame()
op7=>operation: av_write_trailer()
sub1=>subroutine: flush操作
cond=>condition: 继续编码？
e=>end: 结束

st->op->op1->op2->op3->op4->cond
cond(no)->sub1->op7->e
cond(yes)->op5->op6(left)->cond

```

