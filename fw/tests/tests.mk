## Path config
FW_SUBPATH ?= ..
TESTS_PROJECT_FILE := $(FW_SUBPATH)/project.yml

## Ceedling
CEEDLING_CMD := cd $(FW_SUBPATH) && ceedling

tests: .tests

.tests: $(TESTS_PROJECT_FILE)
	$(CEEDLING_CMD) test:all

coverage: $(TESTS_PROJECT_FILE)
	$(CEEDLING_CMD) gcov:all utils:gcov

tests-clean:
	$(CEEDLING_CMD) clobber

.phony: tests-clean tests coverage
