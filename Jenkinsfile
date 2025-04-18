pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }
        stage('Run Tests') {
            steps {
                sh './tests/bash_testing/basic_tester.sh'
            }
        }
    }
    post {
        always {
            junit 'test-results.xml'
            archiveArtifacts artifacts: '**/testfile', allowEmptyArchive: true
        }
        success {
            echo 'All tests passed!'
        }
        failure {
            echo 'Some tests failed.'
        }
    }
}
