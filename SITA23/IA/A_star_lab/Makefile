COMPILE = ocamlfind ocamlc
COMPILEOPT = ocamlfind ocamlopt
CSLDEP=ocamlfind ocamldep
CAMLLEX=ocamlfind ocamllex
CAMLYACC=ocamlfind ocamlyacc
CAMLDOC= ocamlfind ocamldoc


NORM_FILES= pqueue.ml memory.ml a_star.ml
NORM_OBJS =  $(NORM_FILES:.ml=.cmo)
OPT_OBJS=  $(NORM_FILES:.ml=.cmx)

all : a_star.cma a_star.cmxa doc

doc:
	mkdir doc;$(CAMLDOC) -html -t "A_star" -d doc -intro Intro -hide Pervasives *.mli

a_star.cma: $(NORM_OBJS)
	$(COMPILE) -a -o $@ $(NORM_OBJS)

a_star.cmxa: $(OPT_OBJS)
	$(COMPILEOPT) -a -o $@ $(OPT_OBJS)

.SUFFIXES: .mll .mly .ml .mli .cmo .cmi .cmx

.mll.mli:
	$(CAMLLEX) $<
.mll.ml:
	$(CAMLLEX) $<
.mly.mli:
	$(CAMLYACC) $<
.mly.ml:
	$(CAMLYACC) $<
.ml.cmo :
	$(COMPILE) -c $<
.mli.cmi :
	$(COMPILE) -c $<
.ml.cmx :
	$(COMPILEOPT) -c $<

cleandoc:
	\rm -Rf doc

clean:
	\rm -f *.cmo *.cmi *.cmx *.o *.a *.cma *.cmxa .depend *~ parser.ml parser.mli lexer.ml lexer.mli

.depend:
	$(CSLDEP) $(INCLUDES) *.mli *.ml >.depend

include .depend
